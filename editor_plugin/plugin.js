/**
 * @file Plugin for inserting styles for images added.
 */
( function() {
  var pluginDefinition = {
    // Wrap Drupal plugin in a proxy plugin.
    init: function(editor){

      if (Drupal.settings.wwm_media_alter.styles) {
        for (var index in Drupal.settings.wwm_media_alter.styles) {
          CKEDITOR.addCss(Drupal.settings.wwm_media_alter.styles[index]);
        }
      }
    }
  };
  CKEDITOR.plugins.add( 'wwm_media_alter', pluginDefinition);
} )();
