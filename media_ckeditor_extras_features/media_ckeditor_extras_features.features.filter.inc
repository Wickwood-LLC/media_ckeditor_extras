<?php
/**
 * @file
 * media_ckeditor_extras_features.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function media_ckeditor_extras_features_filter_default_formats() {
  $formats = array();

  // Exported format: Caption HTML.
  $formats['caption_html'] = array(
    'format' => 'caption_html',
    'name' => 'Caption HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_html' => array(
        'weight' => -10,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<a> <em> <strong> <u> <p> ',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ),
      ),
      'filter_autop' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_htmlcorrector' => array(
        'weight' => 10,
        'status' => 1,
        'settings' => array(),
      ),
      'pathologic' => array(
        'weight' => 50,
        'status' => 1,
        'settings' => array(
          'local_paths' => '',
          'protocol_style' => 'full',
        ),
      ),
    ),
  );

  return $formats;
}
