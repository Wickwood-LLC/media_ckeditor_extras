<?php
/**
 * @file
 * media_ckeditor_extras_features.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function media_ckeditor_extras_features_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_link|file|image|form';
  $field_group->group_name = 'group_link';
  $field_group->entity_type = 'file';
  $field_group->bundle = 'image';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Image Link',
    'weight' => '12',
    'children' => array(
      0 => 'field_image_link',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-link field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_link|file|image|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Image Link');

  return $field_groups;
}
