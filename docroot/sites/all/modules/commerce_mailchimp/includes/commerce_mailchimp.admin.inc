<?php

/**
 * @file
 * Administrative callbacks for the Commerce MailChimp module.
 */

/**
 * General settings for the MailChimp Ecommerce API.
 *
 * @ingroup forms
 */
function commerce_mailchimp_settings() {
  $form['order'] = array(
    '#type' => 'fieldset',
    '#title' => t('Order Information Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['order']['commerce_mailchimp_store_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Store ID'),
    '#maxlength' => 20,
    '#size' => 20,
    '#default_value' => variable_get('commerce_mailchimp_store_id', NULL),
    '#description' => 'a unique id for the store sending the order in (20 bytes max)',
  );
  $form['order']['commerce_mailchimp_store_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Store Name'),
    '#default_value' => variable_get('commerce_mailchimp_store_name', $_SERVER['SERVER_NAME']),
    '#description' => ' a "nice" name for the store - typically the base web address (ie, "store.mailchimp.com")',
  );
  $form['order']['product'] = array(
    '#type' => 'fieldset',
    '#title' => t('Product Category'),
  );
  foreach (commerce_product_types() as $type => $product_type) {
    $instances = field_info_instances('commerce_product', $type);
    $options = array('' => '- None -');
    foreach ($instances as $instance) {
      $field_info = field_info_field($instance['field_name']);
      if ($field_info['type'] == 'taxonomy_term_reference') {
        $options[$instance['field_name']] = $instance['label'];
      }
    }
    $form['order']['product']['commerce_mailchimp_category_field_' . $type] = array(
      '#type' => 'select',
      '#title' => $product_type['name'],
      '#options' => $options,
      '#default_value' => variable_get('commerce_mailchimp_category_field_' . $type, ''),
    );
  }
  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('API Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['api']['commerce_mailchimp_cookie_time'] = array(
    '#type' => 'select',
    '#title' => t('Store Campaign Info For'),
    '#options' => array(
      1 => '1 Day',
      7 => '7 Days',
      14 => '14 Days',
      30 => '30 Days',
      45 => '45 Days',
      60 => '60 Days',
      90 => '90 Days'
    ),
    '#default_value' => variable_get('commerce_mailchimp_cookie_time', 30),
    '#description' => 'The length of time to store the cookie containing the campign info sent from MailChimp. Shorter times will more accurately reflect the number of purchase made as a direct result of the email campaign, but may miss customers who make a purchase after the cookie expires. Longer times will catch more purchasing desicions but may end up including purchases that were made but were not nessecarily influenced by the campaign. MailChimp recommends 30 days',
  );

  return system_settings_form($form);
}
