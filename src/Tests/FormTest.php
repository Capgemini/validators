<?php

/**
 * @file
 * Contains \Drupal\validators\Tests\FormTest.
 */

namespace Drupal\validators\Tests;

use Drupal\simpletest\WebTestBase;
use Drupal\Core\Url;

/**
 * Web testing class for Validators.
 *
 * @group validators
 */
class FormTest extends WebTestBase {

  /**
   * The profile to install as a basis for testing.
   *
   * @var string
   */
  protected $profile = 'testing';

  /**
   * The route where the test form can be found.
   *
   * @var string
   */
  protected $formRoute;

  /**
   * The modules to be loaded for these tests.
   */
  public static $modules = ['validators', 'validators_test'];

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    parent::setUp();
    $this->formRoute = Url::fromRoute('validator_form_test');
  }

  /**
   * Tests the form elements.
   */
  public function testSingleValidator() {
    $this->drupalLogin($this->rootUser);
    // All valid.
    $edit = array(
      'email' => $this->randomString() . '@drupal.org',
      'notblank' => $this->randomString(),
      'blank' => '',
      'type' => $this->randomString(),
      'length' => $this->randomString(4),
      'url' => 'http://www.drupal.org',
      'regex' => 'this is a match',
      'ip' => '127.0.0.1',
      'uuid' => '216fff40-98d9-11e3-a5e2-0800200c9a66',
      'range' => 3,
      'equalto' => 'valid',
    );
    $this->drupalPostForm($this->formRoute, $edit, 'Submit');
    $this->assertNoText('This value is not a valid email address.');
    $this->assertNoText('This value should not be blank.');
    $this->assertNoText('This value should be blank.');
    $this->assertNoText('This value should be of type string.');
    $this->assertNoText('This value is too short. It should have 2 characters or more.');
    $this->assertNoText('This value is too short. It should have 2 characters or more.');
    $this->assertNoText('This value is not a valid URL.');
    $this->assertNoText('This value is not valid.');
    $this->assertNoText('This is not a valid IP address.');
    $this->assertNoText('This is not a valid UUID.');
    $this->assertNoText('This value should be 2 or more.');
    $this->assertNoText('This value should be 5 or less.');
    $this->assertNoText('This value should be a valid number.');
    $this->assertNoText('This value should be equal to');

    // Invalid test 1.
    $edit = array(
      'email' => $this->randomString(),
      'blank' => $this->randomString(),
      'length' => $this->randomString(1),
      'url' => $this->randomString(),
      'regex' => $this->randomString(),
      'ip' => $this->randomString(),
      'uuid' => $this->randomString(),
      'range' => 1,
      'equalto' => $this->randomString(),
    );
    $this->drupalPostForm($this->formRoute, $edit, 'Submit');
    $this->assertText('This value is not a valid email address.');
    $this->assertText('This value should be blank.');
    $this->assertText('This value is too short. It should have 2 characters or more.');
    $this->assertText('This value is not a valid URL.');
    $this->assertText('This value is not valid.');
    $this->assertText('This is not a valid IP address');
    $this->assertText('This is not a valid UUID.');
    $this->assertText('This value should be 2 or more.');
    $this->assertText('This value should be equal to');

    // Invalid test 2.
    $edit['length'] = $this->randomString();
    $edit['range'] = 6;
    $this->drupalPostForm($this->formRoute, $edit, 'Submit');
    $this->assertText('This value is too long. It should have 5 characters or less.');
    $this->assertText('This value should be 5 or less.');

    // Invalid test 3.
    $edit['range'] = $this->randomString();
    $this->drupalPostForm($this->formRoute, $edit, 'Submit');
    $this->assertText('This value should be a valid number.');

  }

}
