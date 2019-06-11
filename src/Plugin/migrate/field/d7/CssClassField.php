<?php

namespace Drupal\media_ckeditor_extras\Plugin\migrate\field\d7;

use Drupal\migrate_drupal\Plugin\migrate\field\FieldPluginBase;

/**
 * @MigrateField(
 *   id = "css_class",
 *   type_map = {
 *     "css_class" = "css_class",
 *   },
 *   core = {7},
 *   source_module = "media_ckeditor_extras",
 *   destination_module = "media_ckeditor_extras"
 * )
 */
class CssClassField extends FieldPluginBase {}
