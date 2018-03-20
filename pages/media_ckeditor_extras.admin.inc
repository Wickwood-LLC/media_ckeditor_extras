<?php

function media_ckeditor_extras_settings_form($form, &$form_state) {
  if (!isset($form_state['storage']['mime_icons'])) {
    $form_state['storage']['mime_icons'] = variable_get('mce_mime_icons', array());
  }

  $form['mime_icons'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#prefix' => '<div id="mce-settings-mime-icons">',
    '#suffix' => '</div>',
    '#theme' => 'media_ckeditor_extras_settings_form_mime_icons',
  );
  foreach ($form_state['storage']['mime_icons'] as $index => $mime_icon) {
    $form['mime_icons'][$index]['mime'] = array(
      '#title' => 'Mime',
      '#type' => 'textarea',
      '#default_value' => $mime_icon['mime'],
      '#cols' => 20,
      '#required' => TRUE,
      '#description' => t('Enter one ore more mimes, each mime in separate line.')
    );
    $form['mime_icons'][$index]['icon'] = array(
      '#title' => 'Icon',
      '#type' => 'media',
      '#media_options' => array(
        'global' => array(
          'file_extensions' => 'png gif jpg jpeg',
          'max_filesize'    => '2 MB',
          'uri_scheme'      => 'public',
          'types'           => array('image'),
          'schemes'         => array(
            'public' => 'public',
          ),
        ),
      ),
      '#default_value' => $mime_icon['icon'],
      '#required' => TRUE,
    );
    $form['mime_icons'][$index]['remove'] = array(
      '#type' => 'submit',
      '#value' => t('Remove'),
      '#name' => 'remove_'. $index,
      '#limit_validation_errors' => array(),
      '#submit' => array('media_ckeditor_extras_settings_form_remove_mime_icon_submit'),
      '#ajax' => array(
          'callback' => 'media_ckeditor_extras_settings_form_add_more_mime_icon_callback',
          'wrapper' => 'mce-settings-mime-icons',
      ),
    );
    $form['mime_icons'][$index]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight for @title', array('@title' => $mime_icon['mime'])),
      '#title_display' => 'invisible',
      '#default_value' => $index,
    );
  }

  $form['mime_icons_add_one'] = array(
    '#type' => 'submit',
    '#value' => t('Add more'),
    '#limit_validation_errors' => array(),
    '#submit' => array('media_ckeditor_extras_settings_form_add_more_mime_icon_submit'),
    '#ajax' => array(
        'callback' => 'media_ckeditor_extras_settings_form_add_more_mime_icon_callback',
        'wrapper' => 'mce-settings-mime-icons',
    ),
  );

  $form['submit'] = array (
    '#type' => 'submit',
    '#name' => 'save_settings',
    '#value' => t('Save settings'),
  );


  return $form;
}

function theme_media_ckeditor_extras_settings_form_mime_icons(&$variables) {
  $element = $variables['element'];

  // Filter order (tabledrag).
  $rows = array();
  foreach (element_children($element, TRUE) as $name) {
    $element[$name]['weight']['#attributes']['class'][] = 'icon-order-weight';
    $rows[] = array(
      'data' => array(
        drupal_render($element[$name]['mime']),
        drupal_render($element[$name]['icon']),
        drupal_render($element[$name]['remove']),
        drupal_render($element[$name]['weight']),
      ),
      'class' => array('draggable'),
    );
  }
  $output = drupal_render_children($element);
  $output .= theme('table', array('rows' => $rows, 'attributes' => array('id' => 'mce-mime-icon-order')));
  drupal_add_tabledrag('mce-mime-icon-order', 'order', 'sibling', 'icon-order-weight', NULL, NULL, TRUE);

  return $output;
}

function media_ckeditor_extras_settings_form_add_more_mime_icon_callback($form, $form_state) {
  return $form['mime_icons'];
}

function media_ckeditor_extras_settings_form_add_more_mime_icon_submit($form, &$form_state) {
  $form_state['storage']['mime_icons'][] = array('mime' => '');
  $form_state['rebuild'] = TRUE;
}

function media_ckeditor_extras_settings_form_remove_mime_icon_submit($form, &$form_state) {
  list($temp, $index) = explode('_', $form_state['clicked_button']['#name']);
  unset($form_state['storage']['mime_icons'][(int)$index]);
  $form_state['rebuild'] = TRUE;
}

function media_ckeditor_extras_settings_form_validate($form, &$form_state) {
  if ($form_state['triggering_element']['#name'] != 'save_settings') {
    return;
  }
  foreach ($form_state['values']['mime_icons'] as $index => $mime_icon) {
    if (empty(trim($mime_icon['mime']))) {
      form_set_error('mime_icons][' . $index . '][mime', t('Mime cannot be empty'));
    }
  }
}

function media_ckeditor_extras_settings_form_submit($form, &$form_state) {
  usort($form_state['values']['mime_icons'], function($a, $b){
    if ($a['weight'] == $b['weight']) {
        return 0;
    }
    return ($a['weight'] < $b['weight']) ? -1 : 1;
  });
  variable_set('mce_mime_icons', $form_state['values']['mime_icons']);
  drupal_set_message(t('Configuration settings has been saved.'));
}