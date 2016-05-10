<?php

/**
 * @file
 * Contains \Drupal\drupal_symfony_validator\ValidatorEvent.
 */

namespace Drupal\drupal_symfony_validator\Event;

use Symfony\Component\EventDispatcher\Event;


/**
 * Wraps a validator event for event listeners.
 */
class ValidatorEvent extends Event {

  /**
   * Custom constraint that is used in the form validation.
   *
   * @var string $constraint
   */
  protected $constraint;

  /**
   * Array containing the validators.
   *
   * @var array $validators;
   */
  protected $validators = array();

  /**
   * Constructs a validator event object.
   *
   * @param string $constraint
   *   The custom constraint that is used in the form validation.
   */
  public function __construct($constraint) {
    $this->constraint = strtolower($constraint);
  }

  /**
   * Get the constraint name.
   *
   * @return string
   *   The custom constraint that is used in the form validation.
   */
  public function getConstraint() {
    return $this->constraint;
  }

  /**
   * Add a validator.
   *
   * @param \Symfony\Component\Validator\Constraint $validator
   *   The validator that will be added.
   */
  public function addValidator(\Symfony\Component\Validator\Constraint $validator) {
    $this->validators[] = $validator;
  }

  /**
   * Get the classes that will be used for validating the form.
   *
   * @return array
   *   An array containing \Symfony\Component\Validator\Constraint
   */
  public function getValidators() {
    return $this->validators;
  }

}
