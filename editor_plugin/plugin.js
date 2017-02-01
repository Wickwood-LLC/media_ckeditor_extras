/**
 * @file Plugin for inserting styles for images added.
 */
( function() {
  var pluginDefinition = {
    // Wrap Drupal plugin in a proxy plugin.
    init: function(editor){

      if (Drupal.settings.hasOwnProperty('media_ckeditor_extras') && Drupal.settings.media_ckeditor_extras.hasOwnProperty('styles')) {
        for (var index in Drupal.settings.media_ckeditor_extras.styles) {
          CKEDITOR.addCss(Drupal.settings.media_ckeditor_extras.styles[index]);
        }
      }

      if (Drupal.settings.media_ckeditor_extras.lazysizes_path) {
        var js_path = Drupal.settings.basePath + Drupal.settings.media_ckeditor_extras.lazysizes_path;
        editor.on( 'loaded', function() {
          if (editor.document) {
            var script = CKEDITOR.document.createElement( 'script', {
              attributes : {
                type : 'text/javascript',
                src: js_path,
              }
            });
            var doc = editor.document;
            doc.getHead().append(script);
          }
        });
      }
    }
  };
  CKEDITOR.plugins.add( 'media_ckeditor_extras', pluginDefinition);
} )();
