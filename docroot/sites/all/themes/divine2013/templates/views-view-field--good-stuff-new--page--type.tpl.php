<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>

<?php if ($fields['type']->content == 'Blog - General'): ?>
  <a href="http://GENERAL">See all blogs</a>
<?php endif; ?>

<?php if ($fields['type']->content == 'Blog - Competition'): ?>
  <a href="http://COMPETITION">See all competitions</a>
<?php endif; ?>

<?php if ($fields['type']->content == 'Blog - News'): ?>
  <a href="http://NEWS">See all news</a>
<?php endif; ?>

<?php if ($fields['type']->content == 'Blog - Event'): ?>
  <a href="http://EVENT">See all events</a>
<?php endif; ?>