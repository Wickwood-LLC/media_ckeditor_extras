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

function _media_ckeditor_extras_get_field_current_table($field) {
  $field_current_tbl_name = array_keys($field['storage']['details']['sql']['FIELD_LOAD_CURRENT']);
  return  reset($field_current_tbl_name);
}

function _media_ckeditor_extras_get_field_revision_table($field) {
  $field_revision_tbl_name = array_keys($field['storage']['details']['sql']['FIELD_LOAD_REVISION']);
  return  reset($field_revision_tbl_name);
}

function _media_ckeditor_extras_long_text_field_current_table_get_format_column($field) {
  $table = _media_ckeditor_extras_get_field_current_table($field);
  return $field['storage']['details']['sql']['FIELD_LOAD_CURRENT'][$table]['format'];
}

function _media_ckeditor_extras_long_text_field_revision_table_get_format_column($field) {
  $table = _media_ckeditor_extras_get_field_revision_table($field);
  return $field['storage']['details']['sql']['FIELD_LOAD_REVISION'][$table]['format'];
}

function _media_ckeditor_extras_long_text_field_reassign_text_format($field, $source_formats, $target_format, $content_type = NULL) {
  $field_current_table =  _media_ckeditor_extras_get_field_current_table($field);
  $field_revision_table = _media_ckeditor_extras_get_field_revision_table($field);

  $current_table_format_field = _media_ckeditor_extras_long_text_field_current_table_get_format_column($field);
  $revision_table_format_field = _media_ckeditor_extras_long_text_field_revision_table_get_format_column($field);

  $total_query = db_select($field_current_table, 'f')
    ->condition('f.deleted', 0)
    ->condition('f.entity_type', 'node');
  $total_query->join('node', 'n', 'f.entity_id = n.nid AND f.revision_id = n.vid');
  if (!empty($content_type)) {
    $total_query->condition('n.type', $content_type);
  }
  $current_total_count = $total_query->countQuery()->execute()->fetchField();

  $applicable_query = clone $total_query;
  $applicable_query->condition("f.{$current_table_format_field}", $source_formats, 'IN');
  $current_applicable_count = $applicable_query->countQuery()->execute()->fetchField();

  $query_args = array(':target_format' => $target_format, ':source_formats' => $source_formats);
  if (!empty($content_type)) {
    $content_type_condition = " AND n.type = :content_type ";
    $query_args[':content_type'] = $content_type;
  }
  $sql = "
    UPDATE {{$field_current_table}} AS f
    INNER JOIN node AS n ON f.entity_id = n.nid AND f.revision_id = n.vid
    SET f.$current_table_format_field = :target_format
    WHERE f.deleted = 0 AND
      f.entity_type = 'node' AND
      f.$current_table_format_field IN (:source_formats) $content_type_condition";
  db_query($sql, $query_args);

  $total_query = db_select($field_revision_table, 'f')
    ->condition('f.deleted', 0)
    ->condition('f.entity_type', 'node');
  $total_query->join('node', 'n', 'f.entity_id = n.nid AND f.revision_id = n.vid');
  if (!empty($content_type)) {
    $total_query->condition('n.type', $content_type);
  }
  $revision_total_count = $total_query->countQuery()->execute()->fetchField();

  $applicable_query = clone $total_query;
  $applicable_query->condition("f.{$revision_table_format_field}", $source_formats, 'IN');
  $revision_applicable_count = $applicable_query->countQuery()->execute()->fetchField();

  $query_args = array(':target_format' => $target_format, ':source_formats' => $source_formats);
  if (!empty($content_type)) {
    $content_type_condition = " AND n.type = :content_type ";
    $query_args[':content_type'] = $content_type;
  }
  $sql = "
    UPDATE {{$field_revision_table}} AS f
    INNER JOIN node AS n ON f.entity_id = n.nid AND f.revision_id = n.vid
    SET f.$revision_table_format_field = :target_format
    WHERE f.deleted = 0 AND
      f.entity_type = 'node' AND
      f.$revision_table_format_field IN (:source_formats) $content_type_condition";
  db_query($sql, $query_args);

  printf(
    "%s (%s: %d/%d, %s: %d/%d)\n",
    $field['field_name'],
    $field_current_table, $current_applicable_count, $current_total_count,
    $field_revision_table, $revision_applicable_count, $revision_total_count
  );
}

function _media_ckeditor_extras_configure_long_text_field_to_limit_format($field_instance, $target_format) {
  $filter_formats = filter_formats();

  // Enable text processing.
  $field_instance['settings']['text_processing'] = 1;
  // Check "Limit allowed text formats"
  $field_instance['settings']['better_formats']['allowed_formats_toggle'] = 1;
  // Uncheck all text formats.
  $field_instance['settings']['better_formats']['allowed_formats'] = array();
  foreach ($filter_formats as $format_name => $format) {
    $field_instance['settings']['better_formats']['allowed_formats'][$format_name] = 0;
  }
  // Now check selected format only.
  $field_instance['settings']['better_formats']['allowed_formats'][$target_format] = $target_format;
  // Save field instance configuration.
  field_update_instance($field_instance);
  drupal_set_message(t('Updated "%label" field of %bundle content type', array('%label' => $field_instance['label'], '%bundle' => $field_instance['bundle'])));
}

 /**
  * Implements hook_drush_command().
  */
 function media_ckeditor_extras_drush_command() {
   $items = array();

    $items['media-ckeditor-extras-configure-all-long-text-fields'] = array(
      'description' => "Configure all long-text fields for input format.",
    );

    $items['media-ckeditor-extras-configure-single-long-text-field'] = array(
      'description' => "Configure single long-text field for input format.",
      'arguments' => array(
        'field_instance' => "Field instance in the form of <content-type>:<field-name>. For example, page:body",
        'target_format' => "Target format machine name",
      ),
    );

    $items['media-ckeditor-extras-long-text-values-reassign-formats'] = array(
      'description' => "Re-assign text format for all long text fields of nodes.",
    );

    $items['media-ckeditor-extras-long-text-field-statistics'] = array(
      'description' => "Show number of usage of each text format",
      'arguments' => array(
        'field_instance'        => "Field instance in the form of <content-type>:<field-name>. For example, page:body",
      ),
    );

    $items['media-ckeditor-extras-long-text-field-reassign-format'] = array(
      'description' => "Re-assign text format for a specific content type long text field values.",
      'arguments' => array(
        'field_instance' => "Field instance in the form of <content-type>:<field-name>. For example, page:body",
        'source_format' => "Source format machine name",
        'target_format' => "Target format machine name",
      ),
    );

    $items['media-ckeditor-extras-detect-file-types'] = array(
      'description' => "Detect and assign file types to files that are still having 'default' as file type.",
      'options' => array(
        'type' => 'The type of files to be inspected. By default it will be "default".',
        'non-strict' => 'Do not check passed file type as valid one.',
      ),
    );

   return $items;
 }

/**
 * Drush command to configure all long-text field instances for its text format.
 */
function drush_media_ckeditor_extras_configure_all_long_text_fields() {
  if (!module_exists('better_formats')) {
    drupal_set_message(t('better_formats module is required.'), 'error');
    return;
  }

  // Prepare filter format options for user selection.
  $filter_formats = filter_formats();
  $filter_format_options = array();
  $filter_formats_by_name = array();
  foreach ($filter_formats as $filter_format) {
    $filter_format_options[$filter_format->name] = $filter_format->name;
    $filter_formats_by_name[$filter_format->name] = $filter_format;
  }

  // Ask user to select target text format.
  $target_format_name = drush_choice($filter_format_options, dt('Select text format that is to be used as replacement?'));
  if (empty($target_format_name)) {
    drush_die(dt('You did not choose any text formats.'));
  }
  $target_format = $filter_formats_by_name[$target_format_name]->format;

  $long_text_field_instances = _media_ckeditor_extras_get_long_text_field_instances();
  foreach ($long_text_field_instances as $field_instance) {
    _media_ckeditor_extras_configure_long_text_field_to_limit_format($field_instance, $target_format);
  }
}

function drush_media_ckeditor_extras_configure_single_long_text_field($field_instance_arg, $target_format) {
  list ($content_type_name, $field_instance_name) = explode(':', $field_instance_arg);
  if (!empty($content_type_name)) {
    $content_type = node_type_load($content_type_name);
  }
  if (!empty($field_instance_name) && !empty($content_type)) {
    $field_instance = field_info_instance('node', $field_instance_name, $content_type_name);
  }
  if (empty($content_type) || empty($field_instance)) {
    drupal_set_message(dt('Invalid field instance name.'), 'error');
    return;
  }

  $filter_formats = filter_formats();
  $filter_formats_by_format = array();
  foreach ($filter_formats as $filter_format) {
    $filter_formats_by_format[$filter_format->format] = $filter_format;
  }
  $filter_format_formats = array_keys($filter_formats_by_format);

  if (!in_array($target_format, $filter_format_formats)) {
    drupal_set_message(dt('Invalid target format name.'), 'error');
    return;
  }

  _media_ckeditor_extras_configure_long_text_field_to_limit_format($field_instance, $target_format);
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
    _media_ckeditor_extras_long_text_field_reassign_text_format($field, $source_formats, $target_format);
  }
  drush_invoke('cc', array('all'));
}

function drush_media_ckeditor_extras_long_text_field_statistics($field_instance_arg) {
  list ($content_type_name, $field_instance_name) = explode(':', $field_instance_arg);
  if (!empty($content_type_name)) {
    $content_type = node_type_load($content_type_name);
  }
  if (!empty($field_instance_name) && !empty($content_type)) {
    $field_instance = field_info_instance('node', $field_instance_name, $content_type_name);
  }
  if (empty($content_type) || empty($field_instance)) {
    drupal_set_message(dt('Invalid field instance name.'), 'error');
    return;
  }

  $field = field_info_field($field_instance['field_name']);
  $field_current_table =  _media_ckeditor_extras_get_field_current_table($field);
  $field_revision_table = _media_ckeditor_extras_get_field_revision_table($field);

  $current_table_format_field = _media_ckeditor_extras_long_text_field_current_table_get_format_column($field);
  $revision_table_format_field = _media_ckeditor_extras_long_text_field_revision_table_get_format_column($field);

  print dt("Content type: @content_type, Field: @field", array('@content_type' => $content_type_name, '@field' => $field_instance_name)) . PHP_EOL;

  $total_query = db_select($field_current_table, 'f')
    ->condition('f.deleted', 0)
    ->condition('f.entity_type', 'node');
  $total_query->join('node', 'n', 'f.entity_id = n.nid AND f.revision_id = n.vid');
  $total_query->addExpression('COUNT(f.entity_type)', 'count');
  $total_query->condition('n.type', $content_type_name)
    ->fields('f', array($current_table_format_field))
    ->groupBy('f.' . $current_table_format_field);
  $result = $total_query->execute();
  foreach ($result as $row) {
    print dt('@count items using @format format', array('@count' => $row->count, '@format' => $row->{$current_table_format_field} )) . PHP_EOL;
  }

  print PHP_EOL;
  //var_dump($field_current_table, $field_revision_table);
}

function drush_media_ckeditor_extras_long_text_field_reassign_format($field_instance_arg, $source_format, $target_format) {
  list ($content_type_name, $field_instance_name) = explode(':', $field_instance_arg);
  if (!empty($content_type_name)) {
    $content_type = node_type_load($content_type_name);
  }
  if (!empty($field_instance_name) && !empty($content_type)) {
    $field_instance = field_info_instance('node', $field_instance_name, $content_type_name);
  }
  if (empty($content_type) || empty($field_instance)) {
    drupal_set_message(dt('Invalid field instance name.'), 'error');
    return;
  }

  $filter_formats = filter_formats();
  $filter_formats_by_format = array();
  foreach ($filter_formats as $filter_format) {
    $filter_formats_by_format[$filter_format->format] = $filter_format;
  }
  $filter_format_formats = array_keys($filter_formats_by_format);

  if (!in_array($source_format, $filter_format_formats) || !in_array($target_format, $filter_format_formats)) {
    drupal_set_message(dt('Invalid source and/or target format name.'), 'error');
    return;
  }

  $field = field_info_field($field_instance['field_name']);

  _media_ckeditor_extras_long_text_field_reassign_text_format($field, array($source_format), $target_format, $content_type_name);
}

function drush_media_ckeditor_extras_detect_file_types() {
  $types = file_type_load_all();
  $type = drush_get_option('type', 'default');
  $non_strict  = drush_get_option('non-strict', FALSE);

  if (!$non_strict && !isset($types[$type])) {
    drupal_set_message(dt('@type is not a valid file type.', array('@type' => $type)), 'error');
    return;
  }
  $result = db_select('file_managed', 'f')
    ->fields('f', array('fid', 'filename'))
    ->condition('type', $type)
    ->execute();

  $count = 0;
  $total_count = 0;
  foreach ($result as $row) {
    $file = file_load($row->fid);
    $new_type = file_get_type($file);
    if ($type != $new_type) {
      $file->type = $new_type;
      file_save($file);
      print dt('File type of @filename (fid: @fid) has been changed from "@old_type" to "@new_type".', array('@filename' => $row->filename, '@fid' => $file->fid, '@old_type' => $type, '@new_type' => $new_type )) . PHP_EOL;
      $count++;
    }
    $total_count++;
  }

  drupal_set_message(dt('@count files has been updated.', array('@count' => $count)));

  if ($total_count > $count) {
    drupal_set_message(dt('@count files did not require re-assignment.', array('@count' => $total_count - $count)));
  }
}
