<?php

/**
 * @file
 * Provides Media: WYSIWYG integration for CKEditor.
 */

/**
 * Implements hook_ckeditor_plugin_alter().
 */
function wwm_media_alter_ckeditor_plugin(&$plugins) {
  // Override the default CKEditor Media plugin.
  return array(
    'wwm_media_alter' => array(
      'name' => 'wwm_media_alter',
      'desc' => t('WWM Media Alter'),
      'path' => '%base_path%' . drupal_get_path('module', 'wwm_media_alter') . '/editor_plugin/',
      'default' => 'f',
    )
  );
}
