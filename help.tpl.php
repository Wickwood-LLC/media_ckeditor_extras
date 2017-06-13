<h3>About</h3>
<p>The 'Media CKEditor Extras' module provides some enhancements and features on top of the Media-CKEditor stack. Features implemented by this module include:</p>
<dl>
  <dt>CSS Class field type</dt>
  <dd>This field type is almost same like a 'List text' field. The key values in fields of this type are supposed as CSS classes. Also, there will be extra configuration field called 'CSS styles' in field settings page. Which can be used to add CSS styles. On rendering, those CSS classes will be added to wrapper element of the rendered entity output. CSS styles also will be added to page output. Currently only Image type of Media entity type is supported.</dd>
  <dt>Image Alignment</dt>
  <dd>Submodule 'Media CKEditor Extras Features' brings a field called 'Image placement' which is of 'CSS Class' type mentioned above. Which already have some preconfigured CSS styles. So, you can use this field to align image on right, left or center on output.</dd>
  <dt>Caption</dt>
  <dd>Submodule 'Media CKEditor Extras Features' brings a field 'Caption' which can be used as caption for the images while adding to WYSIWYG editor using Media browser dialog.</dd>
  <dt>Link field</dt>
  <dd>
    User can add a link field in an image type and configure to use it to link the image when rendered.<br/>
    <b>Note:</b> 'Media CKEditor Extras Features' submodule already brings a field 'field_image_link'. You just need to select that field at <?php print l('Image type edit page', 'admin/structure/file-types/manage/image'); ?>.
  </dd>
</dl>

<h3>Configurations Required for Complete Media-CKEditor Stack to Work</h3>
<ul>
  <li>Go to <?php print l('Image type edit page', 'admin/structure/file-types/manage/image'); ?> and select the link field from selection list shown with label 'Link', which you can find under 'Media CKEditor Extras' fieldset.</li>
  <li>Go to <?php print l('Media browser settings', 'admin/config/media/browser'); ?> page and apply following configurations.
    <ul>
      <li>Select "Full file entity rendering" option for "How should file entities be rendered within a text field?" under "WYSIWYG Configuration" section.</li>
      <li>Enable "Display fully rendered files in WYSIWYG" checkbox under "CKEditor WYSIWYG Configuration" section.</li>
      <li>Select "CSS Class" and "Link" fields under "Override field types in WYSIWYG"</li>
    </ul>
  </li>
  <li>Go to "Manage Fields" page for each file type. Edit "Media Placement" field then enable "Override in WYSIWYG" checkbox. Do same for "Image link" field in image file type.</li>
  <li>Go to <?php print l('Permissions', 'admin/people/permissions'); ?> page and grant permissions 'Use the Caption HTML text format' and 'View overridden file entities in wysiwyg' to roles as required. The 'Use the Caption HTML text format' permission should typically be granted to roles like: Contributor, Editor, Administrator and Webmaster. The 'View overridden file entities in wysiwyg'  permission can probably be granted to 'Authenticated User' role.</li>
  <li>Go to <?php print l('CKEditor Global profile', 'admin/config/content/ckeditor/editg'); ?> page. Ensure plugin path on field "Path to the CKEditor plugins directory" is correctly configured. You can specify <strong>'%l/ckeditor/plugins'</strong> if CKEditor is put in libraries directory.</li>
  <li>Go to <?php print l('CKEditor profiles list', 'admin/config/content/ckeditor'); ?> and:
    <ul>
      <li>Make sure to remove the default CKEditor 'Image' and 'Link' buttons and add the 'Media' and 'Linkit' buttons to toolbar of CKEditor profiles that require Media Extras.</li>
      <li>Make sure following plugins are enabled on CKEditor profiles that require Media Extras:
        <ul>
          <li>Support for Linkit module</li>
          <li>Plugin for embedding files using Media CKEditor</li>
          <li>Media CKEditor Extras</li>
        </ul>
      </li>
    </ul>
  </li>
  <li>Go to "<?php print l('Text formats', 'admin/config/content/formats'); ?>" page and for all input formats ensure "Convert Media tags to markup" filter comes before "Convert URLs into links" filter under "Filter processing order" as applicable.</li>
  <li>Confirm that you have "Image" file display enabled for each of view modes at "<?php print l('Manage File Display', 'admin/structure/file-types/manage/image/file-display'); ?>" that need Media CKEditor Extras to work. For responsive images, you have to enable "Picture" file display instead of "Image" (assuming Picture module is already installed and configured).</li>
  <li>To create a view mode to display image with caption:
    <ul>
      <li>Choose sub-tab for the view mode that will have a caption on <?php print l('Manage display', 'admin/structure/file-types/manage/image/display'); ?> page. (If you need to create new one first, you can do that on <?php print l('Entity view modes', 'admin/config/system/entity-view-modes'); ?>. This requires the “entity_view_mode” module.)</li>
      <li>Arrange fields, so that "File" comes first then "Caption" field with label set to "&lt;Hidden&gt;". Make all other fields hidden from displaying.</li>
    </ul>
  </li>
  <li>To restrict available view modes in Media Browser popup:
    <ul>
      <li>Open each view mode sub-tab within <?php print l('Manage File Display', 'admin/structure/file-types/manage/image/file-display'); ?> page.</li>
      <li>Select "Restrict in WYSIWYG" checkbox if that view mode to be not shown in Media Browser popup, then save page.</li>
      <li>Repeat above steps for each file type (image, audio, video, etc) as needed.</li>
    </ul>
  </li>
  <li>To make a media video field output responsive:
    <ul>
      <li>Ensure "Field Formatter Class" module is installed.</li>
      <li>Open "Manage Display" page for that content type and edit field formatter for that field.</li>
      <li>Specify "mce-video-responsive" CSS class within "Field Formatter Class" textfield.</li>
      <li>Click "Update" and click "Save" button on bottom of page to save configuration changes made.</li>
    </ul>
  </li>
</ul>
