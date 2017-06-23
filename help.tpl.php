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
  <li>Go to "<?php print l('Text formats', 'admin/config/content/formats'); ?>" page and for each input format uses the Media CKEditor Extras:
    <ul>
      <li>Select Roles that will have access to Embedding Media in WYSIWYG Editors</li>
      <li>Enable "Convert Media Tags to Markup" and ensure that "Convert Media tags to markup" filter is above "Convert URLs into links" filter under "Filter processing order".
        <ul>
          <li>Note: Media CKEditor Extras Features module should have provided this configuration for the Text Formats it provides, but if you add others you will want to be sure to configure things as above.</li>
        </ul>
      </li>
      <li>Disable the filter "Ensure That Embedded Media Tags Are Not Contained In Paragraphs”. This should be disabled by default.</li>
    </ul>
  </li>
  <li>Confirm that you have "Image" file display enabled and the appropriate Image Style selected for each of view modes at "<?php print l('Manage File Display', 'admin/structure/file-types/manage/image/file-display'); ?>" that need Media CKEditor Extras to work. For responsive images, you have to enable "Picture" file display instead of "Image" (assuming Picture module is already installed and configured).</li>
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
      <li>Above steps should be performed against "WYSIWYG" views mode each file type.</li>
    </ul>
  </li>
  <li>To make a media video field output responsive on Content Types not using Panels or Panelizer:
    <ul>
      <li>Ensure "Field Formatter Class" module is installed.</li>
      <li>Open "Manage Display" page for that content type and edit field formatter for that field.</li>
      <li>Specify "mce-video-responsive" CSS class within "Field Formatter Class" textfield.</li>
      <li>Click "Update" and click "Save" button on bottom of page to save configuration changes made.</li>
    </ul>
  </li>
  <li>To make a media video field output responsive on Content Types that use Panels or Panelizer:
    <ul>
      <li>Set the “CSS Class” to "mce-video-responsive" for the Panel’s CSS Properties.</li>
    </ul>
  </li>
</ul>

<h3>Drush Commands</h3>
<dl>
  <dt>media-ckeditor-extras-list-all-long-text-field-instances</dt>
  <dd>It will output all long text fields in site in &lt;entity-type&gt;:&lt;bundle&gt:&lt;field-name&gt format, one in each line.
  </dd>

  <dt>media-ckeditor-extras-long-text-field-statistics</dt>
  <dd>
    Arguments:
    <ul>
      <li>field_instance: Field instance in the form of &lt;entity-type&gt;:&lt;bundle&gt:&lt;field-name&gt. For example, node:page:body</li>
    </ul>
    <p>Gives information about how much field items are using each text formats.</p>
    <p>Informs if 'Limit Allowed Text Formats' is not enabled.</p>
    <p>Informs about text formats configured as per 'Limit Allowed Text Formats'</p>
    <p>Informs if 'Filtered Text' is disabled.</p>
    <p>Informs about any text format in use but not allowed as per field configuration.</p>
  </dd>

  <dt>media-ckeditor-extras-long-text-field-statistics-bulk</dt>
  <dd>
    Same as "media-ckeditor-extras-long-text-field-statistics" but performs on multiple field instances.
    <p>Please note: field names to be given using pipe ("|"). You can feed this command with output from "media-ckeditor-extras-list-all-long-text-field-instances" command as shown in example below:</p>
    <pre><code>drush media-ckeditor-extras-list-all-long-text-field-instances | drush media-ckeditor-extras-long-text-field-statistics-bulk > ~site-archive-junaid/long-text-fields-list-results.txt</code></pre>
  </dd>

  <dt>media-ckeditor-extras-long-text-field-identify</dt>
  <dd>
    Arguments:
    <ul>
      <li>field_instance_with_format: Field instance with format in the form of &lt;entity-type&gt;:&lt;bundle&gt:&lt;field-name&gt:&lt;format&gt;. For example, node:page:body:full_html</li>
    </ul>
    <p>Lists all field items currently using specified text format.</p>
    <p>Please note that you can omit 'format' part in argument if you want to see items using no formats (NULL).</p>
  </dd>

  <dt>media-ckeditor-extras-long-text-field-reassign-format</dt>
  <dd>
    Arguments:
    <ul>
      <li>field_instance: Field instance in the form of &lt;entity-type&gt;:&lt;bundle&gt:&lt;field-name&gt. For example, node:page:body</li>
      <li>source_format: Source format machine name</li>
      <li>target_format: Target format machine name</li>
    </ul>
    <p>Re-assigns all field items currently using source_format to use target_format.</p>
    <p>Proper analysis should be performed before running this command to check compatibility issues between source and target text formats. Or issues may occur in field output.</p>
  </dd>

  <dt>media-ckeditor-extras-configure-all-long-text-fields</dt>
  <dd>
    Configures all long text fields to limit to single text format. Also performs site wide reassignment from one text format to another. Not useful on most of sites.<br>
    <p>This command will ask you to select text formats to be reassigned.</p>
    <p>Proper analysis should be performed before running this command to check compatibility issues between source and target text formats. Or issues may occur in field output.</p>
  </dd>

  <dt>media-ckeditor-extras-configure-single-long-text-field</dt>
  <dd>
    Arguments:
    <ul>
      <li>field_instance: Field instance in the form of &lt;entity-type&gt;:&lt;bundle&gt:&lt;field-name&gt. For example, node:page:body</li>
      <li>target_format: Target format machine name</li>
    </ul>
    <p>Configure specified field instance to restrict to single text format. It will also reassign all field items to user specified text format.</p>
    <p>Proper analysis should be performed before running this command to check compatibility issues between source and target text formats. Or issues may occur in field output.</p>
  </dd>

  <dt>media-ckeditor-extras-long-text-values-reassign-formats</dt>
  <dd>
    Similar to "media-ckeditor-extras-configure-all-long-text-fields", but only on fields of content types (node types).
  </dd>

  <dt>media-ckeditor-extras-detect-file-types</dt>
  <dd>
    Arguments:
    <ul>
      <li>type: The type of files to be inspected. By default it will be "default".</li>
      <li>non-strict: Do not check file type to be valid one. Useful if file type was disabled or deleted.</li>
    </ul>
    Detect and assign file types to files that are still having 'default' as file type.
  </dd>
</dl>
