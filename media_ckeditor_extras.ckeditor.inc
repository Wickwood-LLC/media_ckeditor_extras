<?php

/**
 * @file
 * Provides Media: WYSIWYG integration for CKEditor.
 */

/**
 * Implements hook_ckeditor_plugin_alter().
 */
function media_ckeditor_extras_ckeditor_plugin() {
  // Override the default CKEditor Media plugin.
  return array(
    'media_ckeditor_extras' => array(
      'name' => 'media_ckeditor_extras',
      'desc' => t('Media CKEditor Extras'),
      'path' => '%base_path%' . \Drupal::service('extension.list.module')->getPath('media_ckeditor_extras') . '/editor_plugin/',
      'default' => 'f',
    )
  );
}
