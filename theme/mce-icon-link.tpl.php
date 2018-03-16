<div class="<?php print $classes ?>"<?php print $attributes; ?>>
  <a href="<?php print $link_url; ?>">
   <?php if ($settings['icon_position'] == 'left' || $settings['icon_position'] == 'top'): ?>
    <span class="icon"><?php print render($icon); ?></span>
    <span class="text"><?php print $link_text; ?></span>
   <?php else: ?>
    <span class="text"><?php print $link_text; ?></span>
    <span class="icon"><?php print render($icon); ?></span>
   <?php endif; ?>
  </a>
</div>