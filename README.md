[![Build Status](https://travis-ci.org/Capgemini/validators.svg?branch=8.x-1.x)]
(https://travis-ci.org/Capgemini/validators)
# Drupal Symfony Validators
"Drupal Symfony Validator" allows you to use the Symfony Validator component
inside your Drupal projects. The module allows you to extend your forms with
an extra parameter called `#validators`. This validator is designed to validate
forms against *constraints* (i.e. rules). An overview of these constraints can
be found on the [official component page]
(http://symfony.com/doc/current/book/validation.html#constraints).

## Requirements
PHP Version: 5.3.x or greater.
Dependencies: [Composer Manager](https://drupal.org/project/composer_manager)

## Basic example
In the following example we will validate if the user filled in a valid e-mail
address and a valid [ISBN number]
(https://en.wikipedia.org/wiki/International_Standard_Book_Number):

```
function mymodule_personal_details_form($form, &$form_state) {

  $form['email_address'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#validators' => array(
      'Email'
    ),
  );

  $form['isbn'] = array(
    '#type' => 'textfield',
    '#title' => t('Bank account (ISBN format)'),
    '#validators' => array(
      'Isbn' => array(
        'message' => t(
          'This value is an invalid bank account number. Please respect the 
           <a href="@url">ISBN format</a>.',
          array('@url' => 
          'https://en.wikipedia.org/wiki/International_Standard_Book_Number')
        ),
      )
    ),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}
```

## Custom constraints
The module allows other modules to implement the 
`hook_validator_asserts()` hook. Implementing this hook allows other
modules to use custom asserts. The hook has to return an empty array or an array
containing an object that is extending `Symfony\Component\Validator\Constraint`.
 
### Example of a custom contraint.

```
...

function mymodule_personal_details_form($form, &$form_state) {

  $form['car_brand'] = array(
    '#type' => 'textfield',
    '#title' => t('The car brand of your car'),
    '#validators' => array(
      'CarBrand'
    ),
  );

...

/**
 * Implements hook_validator_asserts().
 */
function mymodule_validator_asserts($constraint, $options) {
  $asserts = array();

  switch ($constraint) {
    case "CarBrand":
      $asserts[] = new MyModule\Assert\CarBrand($options);
  }

  return $asserts;
}
```
