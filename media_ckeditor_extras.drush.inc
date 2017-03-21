<?php

 /**
  * Implements hook_drush_command().
  */
 function media_ckeditor_extras_drush_command() {
   $items = array();

   $items['media-ckeditor-extras-configure-long-text-fields'] = array(
     'description' => "Configure all long-text fields for input format.",
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

  $node_field_instances = field_info_instances('node');
  foreach ($node_field_instances as $bundle => $content_type_field_instances) {
    foreach ($content_type_field_instances as $field_name => $content_type_field_instance) {
      $field = field_info_field_by_id($content_type_field_instance['field_id']);
      // Only process long-text fields.
      if (in_array($field['type'], array('text_long', 'text_with_summary'))) {
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

  }
}
