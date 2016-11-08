<?php
/**
 * @file
 * media_ckeditor_extras_features.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function media_ckeditor_extras_features_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'file-image-field_image_link'.
  $field_instances['file-image-field_image_link'] = array(
    'bundle' => 'image',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '<p>If you would like to link this image to another page on this site, use the <strong><i>Search Button</i></strong> above to find that page\'s URL or you can just enter it in the <strong><i>Image Link</i></strong> field directly.  If you would like to link to an external site, <strong><i>be sure to include</i></strong> http:// or https:// as part of the URL  in the <strong><i>Image Link</i></strong> field.</p>
<p>To make this link open in a new browser window or tab, enable <strong><i>Open URL in a New Window</i></strong>.  You can also add custom classes to this link as well with the <strong><i>Custom link class</i></strong> field.  When adding multiple classes, separate classes with spaces. Only alphanumeric characters and hyphens are allowed for class names.</p>',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 11,
      ),
      'landscape_290x210_' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_block_thumbnail' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_collection_thumbnail' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_detail' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_lightbox' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_thumbnail' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_link' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_original' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'portrait_210x270_' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'preview_100x100_with_caption' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
      'scale_160x120' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_160x120_rotate_left' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_160x120_rotate_right' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_320x240' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_320x240_rotate_left' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_320x240_rotate_right' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_480x360' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_480x360_rotate_left' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_480x360_rotate_right' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_640x480' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_640x480_rotate_left' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_640x480_rotate_right' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'file',
    'field_name' => 'field_image_link',
    'label' => 'Image link',
    'required' => 0,
    'settings' => array(
      'absolute_url' => 1,
      'attributes' => array(
        'class' => '',
        'configurable_class' => 1,
        'configurable_title' => 0,
        'rel' => '',
        'target' => 'user',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'linkit' => array(
        'button_text' => 'Search',
        'enable' => 1,
        'profile' => 'link_for_media',
      ),
      'rel_remove' => 'default',
      'title' => 'none',
      'title_label_use_field_label' => 0,
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => FALSE,
      'validate_url' => 1,
      'wysiwyg_override' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(),
      'type' => 'link_field',
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'file-image-field_image_placement'.
  $field_instances['file-image-field_image_placement'] = array(
    'bundle' => 'image',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 13,
      ),
      'landscape_290x210_' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_block_thumbnail' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_collection_thumbnail' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_detail' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_lightbox' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_thumbnail' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_link' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_original' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'portrait_210x270_' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'preview_100x100_with_caption' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_160x120' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_160x120_rotate_left' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_160x120_rotate_right' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_320x240' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_320x240_rotate_left' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_320x240_rotate_right' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_480x360' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_480x360_rotate_left' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_480x360_rotate_right' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_640x480' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_640x480_rotate_left' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_640x480_rotate_right' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'file',
    'field_name' => 'field_image_placement',
    'label' => 'Image placement',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
      'wysiwyg_override' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'file-image-field_long_caption'.
  $field_instances['file-image-field_long_caption'] = array(
    'bundle' => 'image',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 12,
      ),
      'landscape_290x210_' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_block_thumbnail' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_collection_thumbnail' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_detail' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_lightbox' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_gallery_thumbnail' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_link' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'media_original' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'portrait_210x270_' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'preview' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'preview_100x100_with_caption' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'scale_160x120' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_160x120_rotate_left' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_160x120_rotate_right' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_320x240' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_320x240_rotate_left' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_320x240_rotate_right' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_480x360' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_480x360_rotate_left' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_480x360_rotate_right' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_640x480' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_640x480_rotate_left' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'scale_640x480_rotate_right' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'file',
    'field_name' => 'field_long_caption',
    'label' => 'Caption',
    'required' => 0,
    'settings' => array(
      'better_formats' => array(
        'allowed_formats' => array(
          1 => 0,
          2 => 0,
          3 => 0,
          5 => 0,
          6 => 0,
          'caption_html' => 'caption_html',
        ),
        'allowed_formats_toggle' => 1,
        'default_order_toggle' => 0,
        'default_order_wrapper' => array(
          'formats' => array(
            1 => array(
              'weight' => -1,
            ),
            2 => array(
              'weight' => 0,
            ),
            3 => array(
              'weight' => 0,
            ),
            5 => array(
              'weight' => 0,
            ),
            6 => array(
              'weight' => 1,
            ),
            'caption_html' => array(
              'weight' => 0,
            ),
          ),
        ),
      ),
      'linkit' => array(
        'button_text' => 'Search',
        'enable' => 0,
        'profile' => '',
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
      'wysiwyg_override' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 14,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('<p>If you would like to link this image to another page on this site, use the <strong><i>Search Button</i></strong> above to find that page\'s URL or you can just enter it in the <strong><i>Image Link</i></strong> field directly.  If you would like to link to an external site, <strong><i>be sure to include</i></strong> http:// or https:// as part of the URL  in the <strong><i>Image Link</i></strong> field.</p>
<p>To make this link open in a new browser window or tab, enable <strong><i>Open URL in a New Window</i></strong>.  You can also add custom classes to this link as well with the <strong><i>Custom link class</i></strong> field.  When adding multiple classes, separate classes with spaces. Only alphanumeric characters and hyphens are allowed for class names.</p>');
  t('Caption');
  t('Image link');
  t('Image placement');

  return $field_instances;
}
