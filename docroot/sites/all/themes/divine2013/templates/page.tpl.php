<?php
/**
 * @file
 * Zen theme's implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $secondary_menu_heading: The title of the menu used by the secondary links.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['header']: Items for the header region.
 * - $page['navigation']: Items for the navigation region, below the main menu (if any).
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['footer']: Items for the footer region.
 * - $page['bottom']: Items to appear at the bottom of the page below the footer.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see zen_preprocess_page()
 * @see template_process()
 */
?>

<div id="page">

  <header id="header">
    <a href="http://www.divinechocolate.com/uk/organic">
      <div class="banner" role="banner" style='background-image:url(<?php echo $header_image; ?>);'></div>
    </a>

    <div id="logo">
      <h1><a href="/uk/">Divine Chocolate</a></h1>
    </div>
   
    <?php if (!drupal_is_front_page()): ?>
      <?php print render($page['header']); ?>
    <?php endif; ?>
    <?php print render($page['nav']); ?>
   
    <div id="swoosh"></div>
  </header>

  <div id="main">  	
  	<?php print render($page['highlighted']); ?>
  	
    <?php print $messages; ?>
    <?php print render($tabs); ?>
    <?php print render($page['help']); ?>
    <?php if ($action_links): ?>
      <ul class="action-links"><?php print render($action_links); ?></ul>
    <?php endif; ?>
    
    <?php print $breadcrumb; ?>
    
	<?php print render($title_prefix); 
	if (isset($node->type)) $nodetype = $node->type; else $nodetype = 'none';
	if ($title && strcmp($nodetype,'product_display') != 0): ?>
    	<h1 class="title" id="page-title"><?php print $title; ?></h1>
    <?php endif; ?>
	<?php print render($title_suffix); ?>
  	
    <div id="content" class="column" role="main">
      <a id="main-content"></a>
      <?php print render($page['content']); ?>
      <?php print $feed_icons; ?>
    </div><!-- /#content -->

    
  
    <?php
      // Render the sidebars to see if there's anything in them.
      $sidebar = render($page['sidebar_first']);
      
    if ($sidebar): ?>
      <aside class="sidebars">
        <?php print $sidebar; ?>
      </aside><!-- /.sidebars -->
    <?php endif; ?>

  <?php print render($page['content_bottom']); ?>
  
  </div><!-- /#main -->

  
  <?php print render($page['footer']); ?>

</div><!-- /#page -->

<?php print render($page['bottom']); ?>
