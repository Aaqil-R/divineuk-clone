<?php

/**
 * @file
 * Coupon free shipping default rules.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_coupon_free_shipping_default_rules_configuration() {
  $rules = array();

  $rule = rules_reaction_rule(array(), array(
    'commerce_coupon_line_item' => array(
      'type' => 'commerce_coupon_line_item',
      'label' => 'commerce coupon line item',
    ))
  );

  $rule->label = t('Redeem a coupon with free shipping');
  $rule->active = TRUE;

  $rule
    ->event('commerce_coupon_redeem')
    ->condition('data_is', array(
      'data:select' => 'coupon:type',
      'op' => '=',
      'value' => 'commerce_coupon_free_shipping',
    ))
    ->condition('entity_has_field', array(
      'entity:select' => 'commerce_order',
      'field' => 'commerce_coupon_order_reference',
    ))
    ->condition('data_is', array(
      'data:select' => 'coupon:is-active',
      'op' => '=',
      'value' => TRUE,
    ))
    ->action('list_add', array(
      'list:select' => 'commerce-order:commerce-coupon-order-reference',
      'item:select' => 'coupon',
      'unique' => 1,
  ));

  $rules['commerce_coupon_redeem_free_shipping'] = $rule;
  $rule = rules_reaction_rule();
  $rule->label = t('Calculate a coupon with free shipping');
  $rule->active = TRUE;
  $rule
    ->event('commerce_shipping_calculate_rate')
    ->condition('entity_has_field', array(
      'entity:select' => 'commerce-line-item:order',
      'field' => 'commerce_coupon_order_reference',
  ));
  $loop = rules_loop(array(
    'list:select' => 'commerce-line-item:order:commerce-coupon-order-reference',
    'item:var' => 'list_coupon',
    'item:label' => t('Current coupon'),
    ))
    ->action('commerce_coupon_free_shipping_apply', array(
    'line_item:select' => 'commerce-line-item',
    'coupon:select' => 'list-coupon',
    'component_name:select' => 'list-coupon:price-component-name',
    'round_mode' => COMMERCE_ROUND_HALF_UP,
  ));
  $rule->action($loop);
  $rules['commerce_coupon_calculate_free_shipping'] = $rule;
  return $rules;
}
