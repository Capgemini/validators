<?php

/**
 * @file
 * Contains \Drupal\drupal_symfony_validator\ValidatorEvents.
 */

namespace Drupal\drupal_symfony_validator\Event;

/**
 * Contains all events thrown while handling Symfony Validator.
 */
final class ValidatorEvents {

  /**
   * The event triggered when there's no Symfony Validator constraint found.
   *
   * This event allows modules to react to a form getting validated when a
   * non-existing Symfony Validator constraint is used.
   * The event listener method receives a Constraint string.
   *
   * @Event
   *
   * @see \Drupal\drupal_symfony_validator\ValidatorEvent
   *
   * @var string
   */
  const CUSTOM_VALIDATION = 'drupal_symfony_validator.custom_validation';

}
