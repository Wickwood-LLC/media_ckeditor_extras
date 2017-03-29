<?php

function _media_ckeditor_extras_get_long_text_fields() {
  $fields = array();
  $node_field_instances = field_info_instances('node');
  foreach ($node_field_instances as $bundle => $content_type_field_instances) {
    foreach ($content_type_field_instances as $field_name => $content_type_field_instance) {
      $field = field_info_field_by_id($content_type_field_instance['field_id']);
      // Only process long-text fields.
      if (in_array($field['type'], array('text_long', 'text_with_summary')) && !isset($fields[$content_type_field_instance['field_id']])) {
        $fields[$content_type_field_instance['field_id']] = $field;
      }
    }
  }
  return $fields;
}

function _media_ckeditor_extras_get_long_text_field_instances() {
  $field_instances = array();
  $node_field_instances = field_info_instances('node');
  foreach ($node_field_instances as $bundle => $content_type_field_instances) {
    foreach ($content_type_field_instances as $field_name => $content_type_field_instance) {
      $field = field_info_field_by_id($content_type_field_instance['field_id']);
      // Only process long-text fields.
      if (in_array($field['type'], array('text_long', 'text_with_summary'))) {
        $field_instances[] = $content_type_field_instance;
      }
    }
  }
  return $field_instances;
}

 /**
  * Implements hook_drush_command().
  */
 function media_ckeditor_extras_drush_command() {
   $items = array();

   $items['media-ckeditor-extras-configure-long-text-fields'] = array(
     'description' => "Configure all long-text fields for input format.",
   );

   $items['media-ckeditor-extras-long-text-values-reassign-formats'] = array(
     'description' => "Re-assign text format for all long text fields of nodes.",
   );

   return $items;
 }

/**
 * Drush command to configure all long-text field instances for its text format.
 */
function drush_media_ckeditor_extras_configure_long_text_fields() {
  $formats = filter_formats();
  if (!isset($formats['full_html'])) {
    drupal_set_message(t('"Full HTML" text format not found.'), 'error');
    return;
  }
  elseif (!module_exists('better_formats')) {
    drupal_set_message(t('better_formats module is required.'), 'error');
    return;
  }

  $long_text_field_instances = _media_ckeditor_extras_get_long_text_field_instances();
  foreach ($long_text_field_instances as $content_type_field_instance) {
    // Enable text processing.
    $content_type_field_instance['settings']['text_processing'] = 1;
    // Check "Limit allowed text formats"
    $content_type_field_instance['settings']['better_formats']['allowed_formats_toggle'] = 1;
    // Uncheck all text formats.
    $content_type_field_instance['settings']['better_formats']['allowed_formats'] = array();
    foreach ($formats as $format_name => $format) {
      $content_type_field_instance['settings']['better_formats']['allowed_formats'][$format_name] = 0;
    }
    // Now check full html format only.
    $content_type_field_instance['settings']['better_formats']['allowed_formats']['full_html'] = 'full_html';
    // Save field instance configuration.
    field_update_instance($content_type_field_instance);
    drupal_set_message(t('Updated "%label" field of %bundle content type', array('%label' => $content_type_field_instance['label'], '%bundle' => $content_type_field_instance['bundle'])));
  }
}

function drush_media_ckeditor_extras_long_text_values_reassign_formats() {
  // Prepare filter format options for user selection.
  $filter_formats = filter_formats();
  $filter_format_options = array();
  $filter_formats_by_name = array();
  foreach ($filter_formats as $filter_format) {
    $filter_format_options[$filter_format->name] = $filter_format->name;
    $filter_formats_by_name[$filter_format->name] = $filter_format;
  }

  // Ask user to select source text formats.
  $source_format_names = drush_choice_multiple($filter_format_options, FALSE, dt('Select text formats that are to be replaced? (Select one or more items)'), '!value', "!value\t\t<-- selected");
  if (empty($source_format_names)) {
    drush_die(dt('You did not choose any text formats.'));
  }

  // Ask user to select target text format.
  $target_format_name = drush_choice($filter_format_options, dt('Select text format that is to be used as replacement?'));
  if (empty($target_format_name)) {
    drush_die(dt('You did not choose any text formats.'));
  }

  $source_formats = array();
  foreach ($source_format_names as $name) {
    $source_formats[] = $filter_formats_by_name[$name]->format;
  }
  $target_format = $filter_formats_by_name[$target_format_name]->format;

  $fields = _media_ckeditor_extras_get_long_text_fields();

  foreach ($fields as  $field) {
    $field_current_tbl_name = array_keys($field['storage']['details']['sql']['FIELD_LOAD_CURRENT']);
    $field_revision_tbl_name = array_keys($field['storage']['details']['sql']['FIELD_LOAD_REVISION']);
    $field_current_table =  reset($field_current_tbl_name);
    $field_revision_table =  reset($field_revision_tbl_name);

    $current_table_format_field = $field['storage']['details']['sql']['FIELD_LOAD_CURRENT'][$field_current_table]['format'];
    $revision_table_format_field = $field['storage']['details']['sql']['FIELD_LOAD_REVISION'][$field_revision_table]['format'];

    $total_query = db_select($field_current_table, 'f')
      ->condition('f.deleted', 0)
      ->condition('f.entity_type', 'node');
    $total_query->join('node', 'n', 'f.entity_id = n.nid AND f.revision_id = n.vid');
    $current_total_count = $total_query->countQuery()->execute()->fetchField();

    $applicable_query = clone $total_query;
    $applicable_query->condition("f.{$current_table_format_field}", $source_formats, 'IN');
    $current_applicable_count = $applicable_query->countQuery()->execute()->fetchField();

    $sql = "
      UPDATE {{$field_current_table}} AS f
      INNER JOIN node AS n ON f.entity_id = n.nid AND f.revision_id = n.vid
      SET f.$current_table_format_field = :target_format
      WHERE f.deleted = 0 AND
        f.entity_type = 'node' AND
        f.$current_table_format_field IN (:source_formats)";
    db_query($sql, array(':target_format' => $target_format, ':source_formats' => $source_formats));

    $total_query = db_select($field_revision_table, 'f')
      ->condition('f.deleted', 0)
      ->condition('f.entity_type', 'node');
    $total_query->join('node', 'n', 'f.entity_id = n.nid AND f.revision_id = n.vid');
    $revision_total_count = $total_query->countQuery()->execute()->fetchField();

    $applicable_query = clone $total_query;
    $applicable_query->condition("f.{$revision_table_format_field}", $source_formats, 'IN');
    $revision_applicable_count = $applicable_query->countQuery()->execute()->fetchField();

    $sql = "
      UPDATE {{$field_revision_table}} AS f
      INNER JOIN node AS n ON f.entity_id = n.nid AND f.revision_id = n.vid
      SET f.$revision_table_format_field = :target_format
      WHERE f.deleted = 0 AND
        f.entity_type = 'node' AND
        f.$revision_table_format_field IN (:source_formats)";
    db_query($sql, array(':target_format' => $target_format, ':source_formats' => $source_formats));

    printf(
      "%s (%s: %d/%d, %s: %d/%d)\n",
      $field['field_name'],
      $field_current_table, $current_applicable_count, $current_total_count,
      $field_revision_table, $revision_applicable_count, $revision_total_count
    );
  }
  drush_invoke('cc', array('all'));
}
