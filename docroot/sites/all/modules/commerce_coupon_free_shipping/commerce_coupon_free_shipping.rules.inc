<?php

/**
 * @file
 * Coupon Free Shipping rules integration file.
 */

/**
 * Implements hook_rules_action_info().
 */
function commerce_coupon_free_shipping_rules_action_info() {
  $actions = array();
  $actions['commerce_coupon_free_shipping_apply'] = array(
    'label' => t('Apply a free shipping to order'),
    'parameter' => array(
      'line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Line item'),
      ),
      'coupon' => array(
        'type' => 'commerce_coupon',
        'label' => t('Coupon'),
      ),
      'component_name' => array(
        'type' => 'text',
        'label' => t('Price component type'),
        'description' => t('Price components track changes to prices made during the price calculation process, and they are carried over from the unit price to the total price of a line item. When an order total is calculated, it combines all the components of every line item on the order. When the unit price is altered by this action, the selected type of price component will be added to its data array and reflected in the order total display when it is formatted with components showing. Defaults to base price, which displays as the order Subtotal.'),
        'options list' => 'commerce_price_component_titles',
        'default value' => 'base_price',
      ),
    ),
    'base' => 'commerce_coupon_free_shipping_apply_to_order',
    'group' => t('Commerce Coupon'),
  );

  return $actions;
}

/**
 * Apply the coupon to order.
 */
function commerce_coupon_free_shipping_apply_to_order($line_item, $coupon, $component_name) {
  if ($coupon->is_active != TRUE || $coupon->type != 'commerce_coupon_free_shipping') {
    return;
  }

  $coupon_wrapper = entity_metadata_wrapper('commerce_coupon', $coupon);
  $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);

  // Get the price component to use in this price.
  $price_component_name = $coupon_wrapper->price_component_name->value();
  $unit_price = commerce_price_wrapper_value($line_item_wrapper, 'commerce_unit_price', TRUE);

  // Calculate the updated amount and create a price array representing the
  // difference between it and the current amount.
  $amount = $unit_price['amount'];
  $difference = array(
    'amount' => -1 * $amount,
    'currency_code' => $unit_price['currency_code'],
    'data' => array(),
  );
  // Set the amount of the unit price and add the difference as a component.
  $line_item_wrapper->commerce_unit_price->amount = 0;
  $line_item_wrapper->commerce_unit_price->data = commerce_price_component_add($line_item_wrapper->commerce_unit_price->value(), $price_component_name, $difference, TRUE);
}
