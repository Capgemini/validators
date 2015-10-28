<?php
/**
 * @file
 * Provides the functions that interact with the Symfony Validator.
 */

use Symfony\Component\Validator\Validation;
use Symfony\Component\Validator\Constraint;

/**
 * Processes validation.
 *
 * @param string $value
 *   The value that needs to be validated.
 * @param \Symfony\Component\Validator\Constraint $constraint
 *   The constraint for checking the value with.
 *
 * @return array
 *   An array containing error messages in case of validation errors.
 */
function _drupal_symfony_validator_process_validation($value, Constraint $constraint) {
  $validator = Validation::createValidator();
  $violations = $validator->validate($value, $constraint);

  $form_errors = array();
  for ($i = 0; $i < $violations->count(); $i++) {
    $violation = $violations->get($i);
    $form_errors[] = $violation->getMessage();
  }
  return $form_errors;
}

/**
 * Get violations.
 *
 * @param string $constraint
 *   The constraint that needs to be validated. Can be any of the constraints
 *   used by the Symfony Validator component.
 * @param string $value
 *   The value that needs to be validated.
 * @param array $options
 *   A list of options that need to be used by the constraint.
 *
 * @see http://symfony.com/doc/current/book/validation.html#supported-constraints
 *
 * @return array|null
 *   Returns NULL if the constraint does not exist. An array containing the
 *   violations messages if any violations persist. An empty array if there are
 *   no violations.
 */
function drupal_symfony_validator_get_violations($constraint, $value, array $options = array()) {
  module_load_include('inc', 'drupal_symfony_validator', 'drupal_symfony_validator.asserts');
  $violations = array();

  $functions = array(
    'isnull' => 'is_null',
    'istrue' => 'is_true',
    'isfalse' => 'is_false',
    'notblank' => 'not_blank',
    'notnull' => 'not_null',
    'equalto' => 'equal_to',
    'notequalto' => 'not_equal_to',
    'identicalto' => 'identical_to',
    'lessthan' => 'less_than',
    'lessthanorequal' => 'less_than_or_equal',
    'greaterthan' => 'greater_than',
    'greaterthanorequal' => 'greater_than_or_equal',
    'cardscheme' => 'card_scheme',
  );

  $assert = array_key_exists(strtolower($constraint), $functions) ? $functions[strtolower($constraint)] : $constraint;
  $function = 'drupal_symfony_validator_assert_' . $assert;

  // Check if drupal_symfony_validator has an assertion for the given
  // constraint.
  if (function_exists($function)) {
    $violations = call_user_func($function, $value, $options);
  }
  // Check if another module is delivering an assertion for the given
  // constraint.
  else {
    foreach (module_invoke_all('validator_asserts', $constraint, $options) as $custom_constraint) {
      if (is_subclass_of($custom_constraint, 'Symfony\Component\Validator\Constraint')){
        foreach (drupal_symfony_validator_assert_hook($value, $custom_constraint) as $custom_violation) {
          $violations[] = $custom_violation;
        }
      }
      else {
        drupal_set_message(t('Class @class is not extending Symfony\Component\Validator\Constraint', array('@class' => get_class($custom_constraint))), 'error');
      }
    }
  }

  return $violations;
}
