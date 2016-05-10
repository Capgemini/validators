<?php

/**
 * @file
 * Documentation for Drupal Symfony Validator API.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Introduce a custom validator assertion.
 *
 * Drupal Symfony Validator ships with a lot of out-of-the box assertions. Some
 * modules require more advanced assertions to be validated against. This hook
 * allows a module to introduce a custom assertion to the the Drupal Symfony
 * Validator module.
 *
 * @param string $constraint
 *   The constraint that is used inside the '#validator' parameter of the form
 *   that is getting validated.
 * @param array $options
 *   A list of options that are set inside the form's '#validator' parameter.
 *
 * @return Symfony\Component\Validator\Constraint
 *   This hook needs to return either an empty array or an array that contains a
 *   class which implements Symfony's Constraint class.
 */
function hook_validator_asserts($constraint, $options) {
  $asserts = array();

  switch ($constraint) {
    case "CarBrand":
      $asserts[] = new Assert\CarBrand($options);
      break;
  }

  return $asserts;
}

/**
 * @} End of "addtogroup hooks".
 */
