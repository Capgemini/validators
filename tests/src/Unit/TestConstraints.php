<?php

/**
 * @file
 * Contains \Drupal\Tests\validator\Unit\TestConstraints.
 */

namespace Drupal\Tests\validators\Unit;

use Drupal\Core\DependencyInjection\ContainerBuilder;
use Drupal\validators\ValidatorsManager;
use Drupal\Tests\UnitTestCase;

/**
 * @coversDefaultClass \Drupal\validators\ValidatorsManager
 * @group validators
 */
class TestConstraints extends UnitTestCase {

  /**
   * The validator service.
   *
   * @var ValidatorsManager $validatorsManager
   */
  protected $validatorsManager;

  /**
   * {@inheritdoc}
   */
  public function setUp() {
    $container = new ContainerBuilder();
    $validator = $this->getMockBuilder('\Drupal\validator\Validator')
      ->disableOriginalConstructor()
      ->getMock();
    $validator
      ->method('violations')
      ->willReturn(array());
    $event = $this->getMockBuilder('\Drupal\validators\Event\ValidatorsEvent')
      ->disableOriginalConstructor()
      ->getMock();
    $event
      ->method('getValidators')
      ->willReturn(array());
    $event_dispatcher = $this->getMockBuilder('\Symfony\Component\EventDispatcher\EventDispatcher')
      ->disableOriginalConstructor()
      ->getMock();
    $event_dispatcher->method('dispatch')
      ->willReturn($event);;
    $container->set('event_dispatcher', $event_dispatcher);
    $container->set('validators.validator', $validator);
    \Drupal::setContainer($container);

    $this->validatorsManager = new ValidatorsManager();
  }

  /**
   * Tests for non-existing constraints.
   */
  public function testNonExistingConstraint() {
    $violations = $this->validatorsManager->violations('NonExistingConstraint', 'string');
    $this->assertArrayEquals(array(), $violations, 'Validating against a non-existing constraint should return an empty array.');
  }

  /**
   * Tests for the behaviour when there are no violations found.
   */
  public function testNoViolations() {
    $violations = $this->validatorsManager->violations('Blank', '');
    $this->assertTrue(is_array($violations), 'Passing a blank value to the blank constraint should return an empty array.');
  }

  /**
   * Tests for the options functionalities.
   */
  public function testOptions() {
    $msg = 'This is my custom error message';
    $violations = $this->validatorsManager->violations('Blank', 'Not so blank', array('message' => $msg));
    $this->assertEquals($msg, $violations[0], 'Adding the message option to a constraint should change the error message.');

    $catched = FALSE;
    try {
      $this->validatorsManager->violations('Blank', 'Not so blank', array('nonexistingoption' => 'Use WordPress'));
    }
    catch (\Symfony\Component\Validator\Exception\InvalidOptionsException $e) {
      $catched = TRUE;
    }
    $this->assertTrue($catched, 'When passing a non-existing option to a constraint, an exception should be thrown.');
  }

  /**
   * Tests for the basic constraints.
   */
  public function testBasicConstraints() {
    $tests = array(
      array(
        'constraint' => 'NotBlank',
        'value' => '',
        'msg' => 'Passing an empty value for the NotBlank constraint should return errors.',
      ),
      array(
        'constraint' => 'Blank',
        'value' => 'Not so blank',
        'msg' => 'Passing a non-empty value for the Blank constraint should return errors.',
      ),
      array(
        'constraint' => 'NotNull',
        'value' => NULL,
        'msg' => 'Passing NULL for the NotNull constraint should return errors.',
      ),
      array(
        'constraint' => 'IsNull',
        'value' => 'Not so null',
        'msg' => 'Passing a string for the Null constraint should return errors.',
      ),
      array(
        'constraint' => 'IsTrue',
        'value' => FALSE,
        'msg' => 'Passing FALSE for the True constraint should return errors.',
      ),
      array(
        'constraint' => 'IsFalse',
        'value' => TRUE,
        'msg' => 'Passing TRUE for the False constraint should return errors.',
      ),
      array(
        'constraint' => 'Type',
        'options' => array('type' => 'bool'),
        'value' => 'This is a string',
        'msg' => 'Passing a string for the Type constraint that checks for a boolean should return errors.',
      ),
    );

    foreach ($tests as $test) {
      $this->assertViolations($test);
    }
  }

  /**
   * Tests for the string constraints.
   */
  public function testStringConstraints() {
    $tests = array(
      array(
        'constraint' => 'Email',
        'value' => 'This is not an e-mail address',
        'msg' => 'Passing an invalid e-mail address for the Email constraint should return errors.',
      ),
      array(
        'constraint' => 'Length',
        'value' => 'Three',
        'options' => array(
          'max' => 2,
        ),
        'msg' => 'Passing a string which does not max the min and max value for the Length constraint should return errors.',
      ),
      array(
        'constraint' => 'Url',
        'value' => 'This is not a URL',
        'msg' => 'Passing an invalid URL for the Url constraint should return errors.',
      ),
      array(
        'constraint' => 'Regex',
        'value' => '1 2 3 numbers',
        'options' => array(
          'pattern' => '/\d/',
        ),
        'msg' => 'Passing a string that does not match the pattern for the Regex constraint should return errors.',
      ),
      array(
        'constraint' => 'Ip',
        'value' => '1234.255.255.255',
        'msg' => 'Passing an invalid IP address for the Ip constraint should return errors.',
      ),
      array(
        'constraint' => 'Uuid',
        'value' => 'This is not a valid UUID',
        'msg' => 'Passing an invalid UUID for the Uuid constraint should return errors.',
      ),
    );

    foreach ($tests as $test) {
      $this->assertViolations($test);
    }
  }

  /**
   * Tests for the number constraints.
   */
  public function testNumberConstraints() {
    $tests = array(
      array(
        'constraint' => 'Range',
        'value' => 1,
        'options' => array(
          'min' => 2,
        ),
        'msg' => 'Passing an integer which is not in the specified range for the Range constraint should return errors.',
      ),
    );

    foreach ($tests as $test) {
      $this->assertViolations($test);
    }
  }

  /**
   * Tests the comparison constraints.
   */
  public function testComparisonConstraints() {
    $this->markTestIncomplete();
  }

  /**
   * Process validation unit test.
   *
   * Tests the array that is being returned by ValidatorsManager::process()
   */
  public function testReturnArray() {
    $constraint = new \Symfony\Component\Validator\Constraints\IsNull();
    $correct_value = NULL;
    $incorrect_value = 'Not so null';

    $violations = $this->validatorsManager->process($correct_value, $constraint);
    $this->assertTrue(is_array($violations), 'When there are no violations, an array should be returned.');
    $this->assertTrue(count($violations) == 0, 'When there are no violations, the returned array should be empty.');

    $violations = $this->validatorsManager->process($incorrect_value, $constraint);
    $this->assertTrue(is_array($violations), 'When there are violations, an array should be returned.');
    $this->assertTrue(count($violations) > 0, 'When there are violations, the returned array should contain at least one element.');

    foreach ($violations as $key => $value) {
      $this->assertTrue(is_numeric($key), 'When there are violations, the key of the returned array should be numeric.');
      $this->assertTrue(is_string($value), 'When there are violations, the value of each array element should be a string.');
    }
  }

  /**
   * Helper method that will test a given constraint.
   *
   * @param array $test
   *   An array containing the constraint, value and options for a validation.
   */
  protected function assertViolations(array $test) {
    if (!array_key_exists('options', $test)) {
      $test['options'] = array();
    }
    $violations = $this->validatorsManager->violations($test['constraint'], $test['value'], $test['options']);
    $this->assertTrue(is_array($violations), $test['msg']);
  }

}
