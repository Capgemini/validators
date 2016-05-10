<?php
/**
 * @file
 * Contains \Drupal\drupal_symfony_validator_test\Form\TestForm.
 */

namespace Drupal\drupal_symfony_validator_test\Form;

use Drupal\Core\Form\FormBase;
use Drupal\Core\Form\FormStateInterface;

/**
 * Contribute form.
 */
class TestForm extends FormBase {
  /**
   * {@inheritdoc}
   */
  public function getFormId() {
    return 'drupal_symfony_validator_test_form';
  }

  /**
   * {@inheritdoc}
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $form['email'] = array(
      '#type' => 'textfield',
      '#title' => t('Email default valid'),
      '#validators' => array(
        'Email',
      ),
    );

    $form['notblank'] = array(
      '#type' => 'textfield',
      '#title' => t('Notblank'),
      '#validators' => array(
        'NotBlank',
      ),
    );

    $form['blank'] = array(
      '#type' => 'textfield',
      '#title' => t('Blank'),
      '#validators' => array(
        'Blank',
      ),
    );

    $form['type'] = array(
      '#type' => 'textfield',
      '#title' => t('Type'),
      '#validators' => array(
        'Type' => array(
          'type' => 'string',
        ),
      ),
    );

    $form['length'] = array(
      '#type' => 'textfield',
      '#title' => t('Length'),
      '#validators' => array(
        'Length' => array(
          'min' => 2,
          'max' => 5,
        ),
      ),
    );

    $form['url'] = array(
      '#type' => 'textfield',
      '#title' => t('Url'),
      '#validators' => array(
        'Url',
      ),
    );

    $form['regex'] = array(
      '#type' => 'textfield',
      '#title' => t('Regex'),
      '#validators' => array(
        'Regex' => array(
          'pattern' => '/match/',
        ),
      ),
    );

    $form['ip'] = array(
      '#type' => 'textfield',
      '#title' => t('IP'),
      '#validators' => array(
        'Ip',
      ),
    );

    $form['uuid'] = array(
      '#type' => 'textfield',
      '#title' => t('Uuid'),
      '#validators' => array(
        'Uuid',
      ),
    );

    $form['range'] = array(
      '#type' => 'textfield',
      '#title' => t('Range'),
      '#validators' => array(
        'Range' => array(
          'min' => 2,
          'max' => 5,
        ),
      ),
    );

    $form['equalto'] = array(
      '#type' => 'textfield',
      '#title' => t('EqualTo'),
      '#validators' => array(
        'EqualTo' => array(
          'value' => 'valid',
        ),
      ),
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Submit',
    );

    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, FormStateInterface $form_state) {
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
  }

}
