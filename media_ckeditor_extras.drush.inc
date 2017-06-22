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

/**
 * Return array of all field instances of specified types.
 */
function _media_ckeditor_extras_get_field_instances_by_type($field_types) {
  $field_instances = array();

  $query = db_select('field_config_instance', 'fci')
    ->fields('fci', array('id', 'entity_type', 'bundle', 'field_name'))
    ->condition('fci.deleted', 0);
  $query->join('field_config', 'fc', 'fci.field_id = fc.id');
  $query->condition('fc.type', $field_types, 'IN')
    ->condition('fc.deleted', 0)
    ->orderBy('fci.entity_type', 'ASC')
    ->orderBy('fci.bundle', 'ASC')
    ->orderBy('fci.field_name', 'ASC');
  $result = $query->execute();
  foreach ($result as $row) {
    $field_instances[] = field_info_instance($row->entity_type, $row->field_name, $row->bundle);
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

function _media_ckeditor_extras_long_text_field_reassign_text_format($field, $source_formats, $target_format, $entity_type, $bundle = NULL) {
  $field_current_table =  _media_ckeditor_extras_get_field_current_table($field);
  $field_revision_table = _media_ckeditor_extras_get_field_revision_table($field);

  $current_table_format_field = _media_ckeditor_extras_long_text_field_current_table_get_format_column($field);
  $revision_table_format_field = _media_ckeditor_extras_long_text_field_revision_table_get_format_column($field);

  $entity_info = entity_get_info($entity_type);
  $id_field_name = $entity_info['entity keys']['id'];
  $revision_field_name = $entity_info['entity keys']['revision'];
  $bundle_field_name = $entity_info['entity keys']['bundle'];

  $total_query = db_select($field_current_table, 'f')
    ->condition('f.deleted', 0)
    ->condition('f.entity_type', $entity_type);
  $join_conditions = "f.entity_id = n.{$id_field_name}";
  if (!empty($revision_field_name)) {
    $join_conditions .= " AND f.revision_id = n.{$revision_field_name}";
  }
  $total_query->join($entity_info['base table'], 'n', $join_conditions);
  if (!empty($bundle_field_name) && !empty($bundle)) {
    $total_query->condition("n.{$bundle_field_name}", $bundle);
  }
  $current_total_count = $total_query->countQuery()->execute()->fetchField();

  $applicable_query = clone $total_query;
  $applicable_query->condition("f.{$current_table_format_field}", $source_formats, 'IN');
  $current_applicable_count = $applicable_query->countQuery()->execute()->fetchField();

  $query_args = array(':target_format' => $target_format, ':source_formats' => $source_formats);
  if (!empty($bundle_field_name) && !empty($bundle)) {
    $bundle_condition = " AND n.{$bundle_field_name} = :bundle ";
    $query_args[':bundle'] = $bundle;
  }

  $revision_condition = '';
  if (!empty($revision_field_name)) {
    $revision_condition = "AND f.revision_id = n.{$revision_field_name}";
  }
  $sql = "
    UPDATE {{$field_current_table}} AS f
    INNER JOIN {$entity_info['base table']} AS n ON f.entity_id = n.{$id_field_name} $revision_condition
    SET f.$current_table_format_field = :target_format
    WHERE f.deleted = 0 AND
      f.entity_type = '$entity_type' AND
      f.$current_table_format_field IN (:source_formats) $bundle_condition";
  db_query($sql, $query_args);

  $total_query = db_select($field_revision_table, 'f')
    ->condition('f.deleted', 0)
    ->condition('f.entity_type', $entity_type);
  $join_conditions = "f.entity_id = n.{$id_field_name}";
  if (!empty($revision_field_name)) {
    $join_conditions .= " AND f.revision_id = n.{$revision_field_name}";
  }
  $total_query->join($entity_info['base table'], 'n', $join_conditions);
  if (!empty($bundle_field_name) && !empty($bundle)) {
    $total_query->condition("n.{$bundle_field_name}", $bundle);
  }
  $revision_total_count = $total_query->countQuery()->execute()->fetchField();

  $applicable_query = clone $total_query;
  $applicable_query->condition("f.{$revision_table_format_field}", $source_formats, 'IN');
  $revision_applicable_count = $applicable_query->countQuery()->execute()->fetchField();

  $query_args = array(':target_format' => $target_format, ':source_formats' => $source_formats);
  if (!empty($bundle_field_name) && !empty($bundle)) {
    $bundle_condition = " AND n.{$bundle_field_name} = :bundle ";
    $query_args[':bundle'] = $bundle;
  }
  $revision_condition = '';
  if (!empty($revision_field_name)) {
    $revision_condition = "AND f.revision_id = n.{$revision_field_name}";
  }
  $sql = "
    UPDATE {{$field_revision_table}} AS f
    INNER JOIN {$entity_info['base table']} AS n ON f.entity_id = n.{$id_field_name} $revision_condition
    SET f.$revision_table_format_field = :target_format
    WHERE f.deleted = 0 AND
      f.entity_type = '$entity_type' AND
      f.$revision_table_format_field IN (:source_formats) $bundle_condition";
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
  drupal_set_message(t('Updated "!label" field of @bundle @entity_type', array('!label' => $field_instance['label'], '@bundle' => $field_instance['bundle'], '@entity_type' => $field_instance['entity_type'])));
}

 /**
  * Implements hook_drush_command().
  */
 function media_ckeditor_extras_drush_command() {
   $items = array();

    $items['media-ckeditor-extras-list-all-long-text-field-instances'] = array(
     'description' => "List all long-text field instances in the site. It outputs each field instance in the form <entity-type>:<bundle>:<field-name>, one in each line.",
    );

    $items['media-ckeditor-extras-configure-all-long-text-fields'] = array(
      'description' => "Configure all long-text fields for input format.",
    );

    $items['media-ckeditor-extras-configure-single-long-text-field'] = array(
      'description' => "Configure single long-text field for input format.",
      'arguments' => array(
        'field_instance' => "Field instance in the form of <entity-type>:<bundle>:<field-name>. For example, node:page:body",
        'target_format' => "Target format machine name",
      ),
    );

    $items['media-ckeditor-extras-long-text-values-reassign-formats'] = array(
      'description' => "Re-assign text format for all long text fields of nodes.",
    );

    $items['media-ckeditor-extras-long-text-field-statistics'] = array(
      'description' => "Show number of usage of each text format",
      'arguments' => array(
        'field_instance'        => "Field instance in the form of <entity-type>:<bundle>:<field-name>. For example, node:page:body",
      ),
    );

    $items['media-ckeditor-extras-long-text-field-statistics-bulk'] = array(
      'description' => "Show number of usage of each text format in each fields provided. Field instances in the form of <entity-type>:<bundle>:<field-name>, one in each line to be provided. Empty lines will be ignored.",
    );

    $items['media-ckeditor-extras-long-text-field-reassign-format'] = array(
      'description' => "Re-assign text format for a specific entity type, bundle long text field values.",
      'arguments' => array(
        'field_instance' => "Field instance in the form of <entity-type>:<bundle>:<field-name>. For example, node:page:body",
        'source_format' => "Source format machine name",
        'target_format' => "Target format machine name",
      ),
    );

    $items['media-ckeditor-extras-long-text-field-identify'] = array(
      'description' => "Show field items using specified particular format",
      'arguments' => array(
        'field_instance_with_format' => "Field instance in the form of <entity-type>:<bundle>:<field-name>:<format>. For example, node:page:body:full_html",
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

function drush_media_ckeditor_extras_list_all_long_text_field_instances() {
  $long_text_field_instances = _media_ckeditor_extras_get_field_instances_by_type(array('text_long', 'text_with_summary'));
  foreach ($long_text_field_instances as $field_instance) {
    print dt("@entity_type:@bundle:@field_name", array('@entity_type' => $field_instance['entity_type'], '@bundle' => $field_instance['bundle'], '@field_name' => $field_instance['field_name'])) . PHP_EOL;
  }
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

  $long_text_field_instances = _media_ckeditor_extras_get_field_instances_by_type(array('text_long', 'text_with_summary'));
  foreach ($long_text_field_instances as $field_instance) {
    _media_ckeditor_extras_configure_long_text_field_to_limit_format($field_instance, $target_format);
  }
}

function drush_media_ckeditor_extras_configure_single_long_text_field($field_instance_arg, $target_format) {
  list ($entity_type, $bundle, $field_instance_name) = explode(':', $field_instance_arg);
  if (!empty($entity_type) && !empty($bundle) && !empty($field_instance_name)) {
    $field_instance = field_info_instance($entity_type, $field_instance_name, $bundle);
  }
  if (empty($field_instance)) {
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
    _media_ckeditor_extras_long_text_field_reassign_text_format($field, $source_formats, $target_format, 'node');
  }
  drush_invoke('cc', array('all'));
}

function drush_media_ckeditor_extras_long_text_field_statistics($field_instance_arg) {
  list ($entity_type, $bundle, $field_instance_name) = explode(':', $field_instance_arg);
  if (!empty($bundle)) {
    $content_type = node_type_load($bundle);
  }
  if (!empty($entity_type) && !empty($bundle) && !empty($field_instance_name)) {
    $field_instance = field_info_instance($entity_type, $field_instance_name, $bundle);
  }
  if (empty($field_instance)) {
    drupal_set_message(dt('Invalid field instance name.'), 'error');
    return;
  }

  $field = field_info_field($field_instance['field_name']);
  $field_current_table =  _media_ckeditor_extras_get_field_current_table($field);
  $field_revision_table = _media_ckeditor_extras_get_field_revision_table($field);

  $current_table_format_field = _media_ckeditor_extras_long_text_field_current_table_get_format_column($field);
  $revision_table_format_field = _media_ckeditor_extras_long_text_field_revision_table_get_format_column($field);

  print dt("Entity type: @entity_type, Bundle: @bundle, Field: @field", array('@entity_type' => $entity_type, '@bundle' => $bundle, '@field' => $field_instance_name)) . PHP_EOL;

  $entity_info = entity_get_info($entity_type);
  $id_field_name = $entity_info['entity keys']['id'];
  $revision_field_name = $entity_info['entity keys']['revision'];
  $bundle_field_name = $entity_info['entity keys']['bundle'];

  $total_query = db_select($field_current_table, 'f')
    ->condition('f.deleted', 0)
    ->condition('f.entity_type', $entity_type);

  $join_conditions = "f.entity_id = n.{$id_field_name}";
  if (!empty($revision_field_name)) {
    $join_conditions .= " AND f.revision_id = n.{$revision_field_name}";
  }
  $total_query->join($entity_info['base table'], 'n', $join_conditions);
  $total_query->addExpression('COUNT(f.entity_type)', 'count');
  if (!empty($bundle_field_name)) {
    $total_query->condition("n.{$bundle_field_name}", $bundle);
  }
  $total_query
    ->fields('f', array($current_table_format_field))
    ->groupBy('f.' . $current_table_format_field);
  $result = $total_query->execute();

  $formats_being_used = array();
  if ($result->rowCount()) {
    foreach ($result as $row) {
      $format = $row->{$current_table_format_field} === NULL
        ? 'NULL'
        : $row->{$current_table_format_field};
      $formats_being_used[$row->{$current_table_format_field}] = $format;
      print dt("\t@count items using @format format", array('@count' => $row->count, '@format' => $format )) . PHP_EOL;
    }
  }
  else {
    print dt("\tNo items found.") . PHP_EOL;
  }

  $formats_allowed = array();
  if (isset($field_instance['settings']['text_processing']) &&
      $field_instance['settings']['text_processing'] &&
      isset($field_instance['settings']['better_formats']['allowed_formats'])
  ) {
    $formats_allowed = array_filter($field_instance['settings']['better_formats']['allowed_formats'], function($value){
      return !empty($value);
    });
  }
  if (count($formats_allowed)) {
    print dt("\tFormats allowed in this field are: @formats", array('@formats' => implode(', ', $formats_allowed))) . PHP_EOL;
  }
  else {
    print dt("\tNo formats are configured for this field.") . PHP_EOL;
  }

  $non_configured_formats = array_diff_key($formats_being_used, $formats_allowed);
  if (count($non_configured_formats)) {
    print dt("\tThese formats are not configured but in use: @formats", array('@formats' => implode(', ', $non_configured_formats))) . PHP_EOL;
  }


  print PHP_EOL;
}

function drush_media_ckeditor_extras_long_text_field_statistics_bulk() {
  $field_instances = preg_split ('/$\R?^/m', stream_get_contents(STDIN));
  // Remove empety lines.
  $field_instances = array_filter($field_instances, function($value) {
    return !empty($value);
  });

  foreach ($field_instances as $field_instance) {
    $field_instance = trim($field_instance);
    print dt('Processing @field_instance ...', array('@field_instance' => $field_instance)) . PHP_EOL;
    drush_media_ckeditor_extras_long_text_field_statistics($field_instance);
  }
}

function drush_media_ckeditor_extras_long_text_field_reassign_format($field_instance_arg, $source_format, $target_format) {
  list ($entity_type, $bundle, $field_instance_name) = explode(':', $field_instance_arg);
  if (!empty($entity_type) && !empty($bundle) && !empty($field_instance_name)) {
    $field_instance = field_info_instance($entity_type, $field_instance_name, $bundle);
  }
  if (empty($field_instance)) {
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

  _media_ckeditor_extras_long_text_field_reassign_text_format($field, array($source_format), $target_format, $entity_type, $bundle);
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

function drush_media_ckeditor_extras_long_text_field_identify($field_instance_with_format_arg) {
  list ($entity_type, $bundle, $field_instance_name, $format_name) = explode(':', $field_instance_with_format_arg);
  if (!empty($entity_type) && !empty($bundle) && !empty($field_instance_name)) {
    $field_instance = field_info_instance($entity_type, $field_instance_name, $bundle);
  }
  if (empty($field_instance)) {
    drupal_set_message(dt('Invalid field instance name.'), 'error');
    return;
  }

  $field = field_info_field($field_instance['field_name']);

  // Get main and revision table names for the field.
  $field_current_table =  _media_ckeditor_extras_get_field_current_table($field);
  $field_revision_table = _media_ckeditor_extras_get_field_revision_table($field);

  // Get format fields in db table.
  $current_table_format_field = _media_ckeditor_extras_long_text_field_current_table_get_format_column($field);
  $revision_table_format_field = _media_ckeditor_extras_long_text_field_revision_table_get_format_column($field);

  $entity_info = entity_get_info($entity_type);
  $id_field_name = $entity_info['entity keys']['id'];
  $revision_field_name = $entity_info['entity keys']['revision'];
  $bundle_field_name = $entity_info['entity keys']['bundle'];

  // Prepare and execute query to get all field items using particular text format.
  $query = db_select($field_current_table, 'f')
    ->condition('f.deleted', 0)
    ->condition('f.entity_type', $entity_type);
  $join_conditions = "f.entity_id = n.{$id_field_name}";
  if (!empty($revision_field_name)) {
    $join_conditions .= " AND f.revision_id = n.{$revision_field_name}";
  }
  $query->join($entity_info['base table'], 'n', $join_conditions);
  if (!empty($bundle_field_name) && !empty($bundle)) {
    $query->condition("n.{$bundle_field_name}", $bundle);
  }

  $query->condition("f.{$current_table_format_field}", $format_name);

  $query->addField('f', 'entity_id');
  if (!empty($revision_field_name)) {
    $query->addField('f', 'revision_id');
  }

  $result = $query->execute();

  foreach ($result as $row) {
    if (!empty($revision_field_name)) {
      print dt("Entity id: @id, revision id: @rid", array('@id' => $row->entity_id, '@rid' => $row->revision_id ));
    }
    else {
      print dt("Entity id: @id", array('@id' => $row->entity_id ));
    }
    $entities = entity_load($entity_type, array($row->entity_id));
    if (count($entities)) {
      $uri = entity_uri($entity_type, reset($entities));
      print dt(', URL: "@url"', array('@url' => $uri['path']));
    }
    print PHP_EOL;
  }
}
