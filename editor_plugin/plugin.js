/**
 * @file Plugin for inserting styles for images added.
 */
( function() {
  var pluginDefinition = {
    // Wrap Drupal plugin in a proxy plugin.
    init: function(editor){

      if (Drupal.settings.hasOwnProperty('wwm_media_alter') && Drupal.settings.wwm_media_alter.hasOwnProperty('styles')) {
        for (var index in Drupal.settings.wwm_media_alter.styles) {
          CKEDITOR.addCss(Drupal.settings.wwm_media_alter.styles[index]);
        }
      }
    }
  };
  CKEDITOR.plugins.add( 'wwm_media_alter', pluginDefinition);
} )();
