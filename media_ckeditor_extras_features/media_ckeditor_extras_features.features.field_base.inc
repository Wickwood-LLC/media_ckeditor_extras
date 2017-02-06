<?php
/**
 * @file
 * media_ckeditor_extras_features.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function media_ckeditor_extras_features_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_image_link'.
  $field_bases['field_image_link'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_image_link',
    'field_permissions' => array(
      'type' => 0,
    ),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'link',
    'settings' => array(
      'attributes' => array(
        'class' => '',
        'rel' => '',
        'target' => 'default',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'title' => 'optional',
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
    ),
    'translatable' => 0,
    'type' => 'link_field',
  );

  // Exported field_base: 'field_long_caption'.
  $field_bases['field_long_caption'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_long_caption',
    'field_permissions' => array(
      'type' => 0,
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_long',
  );

  // Exported field_base: 'field_media_placement'.
  $field_bases['field_media_placement'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_media_placement',
    'field_permissions' => array(
      'type' => 0,
    ),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'media_ckeditor_extras',
    'settings' => array(
      'allowed_values' => array(
        'mce-align-left' => 'Left',
        'mce-align-center' => 'Center',
        'mce-align-right' => 'Right',
        'mce-responsive' => 'Responsive full width (Video only)',
      ),
      'allowed_values_function' => '',
      'css_style_text' => 'div.media-element-container.mce-align-center,
div.media-element.mce-align-center {
  display: table;
  margin: 0 auto;
}
div.media-element-container.mce-align-right,
div.media-element.mce-align-right {
  float: right;
  margin-top: 5px;
  margin-left: 5px;
  margin-bottom: 5px;
}

div.media-element-container.mce-align-left,
div.media-element.mce-align-left {
  float: left;
  margin-top: 5px;
  margin-right: 5px;
  margin-bottom: 5px;
}

div.media-element-container.mce-responsive .content ,
div.media-element.mce-responsive .content {
  position: relative;
  padding-bottom: 56.25%; /* 16:9 */
  padding-top: 25px;
  height: 0;
}

div.media-element-container.mce-responsive .file-video .content iframe,
div.media-element.mce-responsive .content img {
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
}',
    ),
    'translatable' => 0,
    'type' => 'css_class',
  );

  return $field_bases;
}
