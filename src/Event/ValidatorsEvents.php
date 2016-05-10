<?php

/**
 * @file
 * Contains \Drupal\validators\ValidatorsEvents.
 */

namespace Drupal\validators\Event;

/**
 * Contains all events thrown while handling Symfony Validator.
 */
final class ValidatorsEvents {

  /**
   * The event triggered when there's no Symfony Validator constraint found.
   *
   * This event allows modules to react to a form getting validated when a
   * non-existing Symfony Validator constraint is used.
   * The event listener method receives a Constraint string.
   *
   * @Event
   *
   * @see \Drupal\validators\ValidatorEvent
   *
   * @var string
   */
  const CUSTOM_VALIDATION = 'validators.custom_validation';

}
