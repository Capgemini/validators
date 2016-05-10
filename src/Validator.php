<?php

/**
 * @file
 * Contains \Drupal\drupal_symfony_validator\Validator.
 */

namespace Drupal\drupal_symfony_validator;

use Symfony\Component\Validator\Constraint;
use Symfony\Component\Validator\Validation;

/**
 * Defines a validator that can be used for validating forms.
 */
class Validator {

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
  public static function process($value, Constraint $constraint) {
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
   * Check if the given constraint exists in Symfony Validator.
   *
   * @param string $constraint
   *   The constraint that needs to be checked.
   * @param array $options
   *   A list of options that needs to be used by the constraint.
   *
   * @return \Symfony\Component\Validator\Constraint | FALSE
   *   The Symfony Validator constraint if it exists, else FALSE.
   */
  private static function &loadAssertClass($constraint, $options = array()) {
    $constraint = "Symfony\\Component\\Validator\\Constraints\\" . $constraint;
    $return = class_exists($constraint) ? new $constraint($options) : FALSE;
    return $return;
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
   * @return array
   *   Returns array containing the violations messages if any violations
   *   persist. An empty array if there are no violations.
   */
  public function violations($constraint, $value, array $options = array()) {
    $violations = array();
    $assert_classes = array();

    // Check if Symfony Validator has an assertion for the given constraint.
    if ($assert_class = self::loadAssertClass($constraint, $options)) {
      $assert_classes[] = $assert_class;
    }
    // Check if another module is delivering an assertion for the given
    // constraint.
    else {
      $e = new Event\ValidatorEvent($constraint);

      /** @var Event\ValidatorEvent $event */
      $event = \Drupal::service('event_dispatcher')
        ->dispatch(Event\ValidatorEvents::CUSTOM_VALIDATION, $e);

      foreach ($event->getValidators() as $custom_constraint) {
        $assert_classes[] = self::loadAssertClass($custom_constraint, $options);
      }
    }

    // Process all the assert classes so that we get a list of violations.
    foreach ($assert_classes as $assert_class) {
      $new_violations = $this->process($value, $assert_class);
      $violations = array_merge($violations, $new_violations);
    }

    return $violations;
  }

}
