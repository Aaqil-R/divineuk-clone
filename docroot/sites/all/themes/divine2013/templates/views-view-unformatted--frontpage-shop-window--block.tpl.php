<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>

<!-- Overiding the styles with a new class when only one result is avaiable -->
<?php 
	$specialClass = '';
	if(count($rows) == 1){
		$specialClass = 'single-column-full-height';
	}
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>
  <div<?php if ($classes_array[$id]) { print ' class="' . $classes_array[$id] . " ". $specialClass .'"';  } ?>>
    <?php print $row; ?>
  </div>
<?php endforeach; ?>