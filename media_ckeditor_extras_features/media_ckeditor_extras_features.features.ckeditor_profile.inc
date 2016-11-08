<?php
/**
 * @file
 * media_ckeditor_extras_features.features.ckeditor_profile.inc
 */

/**
 * Implements hook_ckeditor_profile_defaults().
 */
function media_ckeditor_extras_features_ckeditor_profile_defaults() {
  $data = array(
    'Caption_HTML' => array(
      'name' => 'Caption_HTML',
      'settings' => array(
        'ss' => 2,
        'toolbar' => '[
    [\'Source\',\'RemoveFormat\'],
    [\'Bold\',\'Italic\',\'Underline\',\'Subscript\',\'Superscript\'],
    [\'PasteText\',\'SpellChecker\'],
    [\'JustifyLeft\',\'JustifyCenter\',\'JustifyRight\',\'JustifyBlock\'],
    [\'linkit\',\'Unlink\']
]',
        'expand' => 't',
        'default' => 't',
        'show_toggle' => 't',
        'uicolor' => 'default',
        'uicolor_user' => 'default',
        'width' => '100%',
        'lang' => 'en',
        'auto_lang' => 't',
        'language_direction' => 'default',
        'allowed_content' => 'f',
        'extraAllowedContent' => '',
        'enter_mode' => 'p',
        'shift_enter_mode' => 'br',
        'font_format' => 'p;div;pre;address;h1;h2;h3;h4;h5;h6',
        'custom_formatting' => 't',
        'formatting' => array(
          'custom_formatting_options' => array(
            'indent' => 'indent',
            'breakBeforeOpen' => 'breakBeforeOpen',
            'breakAfterClose' => 'breakAfterClose',
            'breakAfterOpen' => 0,
            'breakBeforeClose' => 0,
            'pre_indent' => 0,
          ),
        ),
        'css_mode' => 'none',
        'css_path' => '',
        'css_style' => 'theme',
        'styles_path' => '',
        'filebrowser' => 'none',
        'filebrowser_image' => '',
        'filebrowser_flash' => '',
        'UserFilesPath' => '%b%f/',
        'UserFilesAbsolutePath' => '%d%b%f/',
        'forcePasteAsPlainText' => 'f',
        'html_entities' => 'f',
        'scayt_autoStartup' => 't',
        'theme_config_js' => 'f',
        'js_conf' => '',
        'loadPlugins' => array(
          'counter' => array(
            'name' => 'counter',
            'desc' => 'Plugin to count symbols, symbols without blanks and words',
            'path' => '%plugin_dir%counter/',
            'buttons' => FALSE,
            'default' => 'f',
          ),
          'linkit' => array(
            'name' => 'linkit',
            'desc' => 'Support for Linkit module',
            'path' => '%base_path%sites/all/modules/linkit/editors/ckeditor/',
            'buttons' => array(
              'linkit' => array(
                'label' => 'Linkit',
                'icon' => 'icons/linkit.png',
              ),
            ),
          ),
          'picture_ckeditor' => array(
            'name' => 'picture_ckeditor',
            'desc' => 'Support responsive images with the Picture module.',
            'buttons' => FALSE,
            'path' => '%base_path%sites/all/modules/picture/ckeditor/plugins/',
            'default' => 't',
          ),
          'sourcedialog' => array(
            'name' => 'sourcedialog',
            'desc' => 'Plugin file: sourcedialog',
            'path' => '%plugin_dir_extra%sourcedialog/',
            'buttons' => FALSE,
            'default' => 'f',
          ),
        ),
      ),
      'input_formats' => array(
        'caption_html' => 'Caption HTML',
      ),
    ),
  );
  return $data;
}
