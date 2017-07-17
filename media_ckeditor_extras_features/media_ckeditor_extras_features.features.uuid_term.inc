<?php
/**
 * @file
 * media_ckeditor_extras_features.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function media_ckeditor_extras_features_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => 'Image Uploads',
    'description' => '',
    'format' => 'panopoly_wysiwyg_text',
    'weight' => 0,
    'uuid' => '05ccc19b-2870-4bda-baee-e9143fcb9aeb',
    'vocabulary_machine_name' => 'media_folders',
    'path' => array(
      'pathauto' => 1,
    ),
    'url_alias' => array(
      0 => array(
        'alias' => 'media-folders/image-uploads',
        'language' => 'und',
      ),
    ),
    'parent' => array(
      0 => 'mbp_uuid_features_root_folder',
    ),
  );
  $terms[] = array(
    'name' => 'Media Root',
    'description' => 'default media folder',
    'format' => NULL,
    'weight' => 9,
    'uuid' => '178b8515-3062-40d2-9b86-61098f5a2068',
    'vocabulary_machine_name' => 'media_folders',
    'url_alias' => array(
      0 => array(
        'alias' => 'media-folders/media-root',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Video Uploads',
    'description' => '',
    'format' => 'panopoly_wysiwyg_text',
    'weight' => 1,
    'uuid' => '1c780b74-7f94-4120-b343-19e535df72a6',
    'vocabulary_machine_name' => 'media_folders',
    'path' => array(
      'pathauto' => 1,
    ),
    'url_alias' => array(
      0 => array(
        'alias' => 'media-folders/video-uploads',
        'language' => 'und',
      ),
    ),
    'parent' => array(
      0 => 'mbp_uuid_features_root_folder',
    ),
  );
  $terms[] = array(
    'name' => 'Document Uploads',
    'description' => '',
    'format' => 'panopoly_wysiwyg_text',
    'weight' => 2,
    'uuid' => '3530528b-250e-4543-bbe6-972db4bbc1a2',
    'vocabulary_machine_name' => 'media_folders',
    'path' => array(
      'pathauto' => 1,
    ),
    'url_alias' => array(
      0 => array(
        'alias' => 'media-folders/document-uploads',
        'language' => 'und',
      ),
    ),
    'parent' => array(
      0 => 'mbp_uuid_features_root_folder',
    ),
  );
  $terms[] = array(
    'name' => 'Other File Uploads',
    'description' => '',
    'format' => 'panopoly_wysiwyg_text',
    'weight' => 8,
    'uuid' => 'b70ab2a7-491a-450a-9dd1-9f590d6751a2',
    'vocabulary_machine_name' => 'media_folders',
    'path' => array(
      'pathauto' => 1,
    ),
    'url_alias' => array(
      0 => array(
        'alias' => 'media-folders/other-file-uploads',
        'language' => 'und',
      ),
    ),
    'parent' => array(
      0 => 'mbp_uuid_features_root_folder',
    ),
  );
  $terms[] = array(
    'name' => 'Test Patterns',
    'description' => '',
    'format' => 'full_html',
    'weight' => 6,
    'uuid' => 'b7cc0be5-6991-466e-9b75-7c7b53fe7a15',
    'vocabulary_machine_name' => 'media_folders',
    'path' => array(
      'pathauto' => 1,
    ),
    'url_alias' => array(
      0 => array(
        'alias' => 'media-folders/test-patterns-and-images',
        'language' => 'und',
      ),
      1 => array(
        'alias' => 'media-folders/test-patterns',
        'language' => 'und',
      ),
    ),
    'parent' => array(
      0 => 'mbp_uuid_features_root_folder',
    ),
  );
  $terms[] = array(
    'name' => 'Audio Uploads',
    'description' => '',
    'format' => 'panopoly_wysiwyg_text',
    'weight' => 3,
    'uuid' => 'bdd72f4f-7472-47c9-91c7-87d719b8abe6',
    'vocabulary_machine_name' => 'media_folders',
    'path' => array(
      'pathauto' => 1,
    ),
    'url_alias' => array(
      0 => array(
        'alias' => 'media-folders/audio-uploads',
        'language' => 'und',
      ),
    ),
    'parent' => array(
      0 => 'mbp_uuid_features_root_folder',
    ),
  );
  $terms[] = array(
    'name' => 'Test Videos, Audios and Documents',
    'description' => '',
    'format' => 'full_html',
    'weight' => 7,
    'uuid' => 'cd6fa767-3014-445e-9af4-41c815c0a83b',
    'vocabulary_machine_name' => 'media_folders',
    'path' => array(
      'pathauto' => 1,
    ),
    'url_alias' => array(
      0 => array(
        'alias' => 'media-folders/test-videos',
        'language' => 'und',
      ),
      1 => array(
        'alias' => 'media-folders/test-videos-audios-and-documents',
        'language' => 'und',
      ),
    ),
    'parent' => array(
      0 => 'mbp_uuid_features_root_folder',
    ),
  );
  $terms[] = array(
    'name' => 'User Profile Images',
    'description' => '',
    'format' => 'full_html',
    'weight' => 4,
    'uuid' => 'de1c5185-f36a-48b9-a4fd-f1d75e1ae672',
    'vocabulary_machine_name' => 'media_folders',
    'path' => array(
      'pathauto' => 1,
    ),
    'url_alias' => array(
      0 => array(
        'alias' => 'media-folders/user-profile-images',
        'language' => 'und',
      ),
    ),
    'parent' => array(
      0 => 'mbp_uuid_features_root_folder',
    ),
  );
  $terms[] = array(
    'name' => 'Backgrounds and Overlays',
    'description' => '',
    'format' => 'full_html',
    'weight' => 5,
    'uuid' => 'e21341f8-cb27-499e-8eaf-7f476d4f0ac3',
    'vocabulary_machine_name' => 'media_folders',
    'path' => array(
      'pathauto' => 1,
    ),
    'url_alias' => array(
      0 => array(
        'alias' => 'media-folders/backgrounds-and-overlays',
        'language' => 'und',
      ),
    ),
    'parent' => array(
      0 => 'mbp_uuid_features_root_folder',
    ),
  );
  return $terms;
}
