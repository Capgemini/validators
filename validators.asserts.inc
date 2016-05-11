<?php
/**
 * @file
 * Provides the assert functions that will check for violations.
 */

use Symfony\Component\Validator\Constraints as Assert;

function validators_assert_hook($value, $constraint) {
  return _validators_process_validation($value, $constraint);
}
/**
 * Assert not blank.
 *
 * Validates that a value is not blank, defined as not strictly false, not equal
 * to a blank string and also not equal to null. To force that a value is simply
 * not equal to null, see validators_assert_not_null().
 *
 * Options:
 * - message: (optional) (string) (Default: 'This value should not be blank.')
 *   This is the message that will be shown if the value is blank.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see validators_assert_not_null()
 */
function validators_assert_not_blank($value, $options = array()) {
  $constraint = new Assert\NotBlank($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert blank.
 *
 * Validates that a value is blank, defined as equal to a blank string or equal
 * to null. To force that a value strictly be equal to null, see the
 * validators_assert_is_null() constraint. To force that a value
 * is not blank, see validators_assert_not_blank().
 *
 * Options:
 * - message: (optional) (string) (Default: 'This value should be blank.') This
 *   is the message that will be shown if the value is not blank.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see validators_assert_is_null()
 * @see validators_assert_not_blank()
 */
function validators_assert_blank($value, $options = array()) {
  $constraint = new Assert\Blank($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert not null.
 *
 * Validates that a value is not strictly equal to null. To ensure that a value
 * is simply not blank (not a blank string), see the
 * validators_assert_not_blank constraint.
 *
 * Options:
 * - message: (optional) (string) (Default: 'This value should not be null.')
 *   This is the message that will be shown if the value is null.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see validators_assert_not_blank()
 */
function validators_assert_not_null($value, $options = array()) {
  $constraint = new Assert\NotNull($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert null.
 *
 * Validates that a value is exactly equal to null. To force that a property is
 * simply blank (blank string or null), see the
 * validators_assert_blank() constraint. To ensure that a property
 * is not null, see validators_assert_not_null().
 *
 * Options:
 * - message: (optional) (string) (Default: 'This value should be null.') This
 *   is the message that will be shown if the value is not null.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see validators_assert_not_null()
 * @see validators_assert_blank()
 */
function validators_assert_is_null($value, $options = array()) {
  $constraint = new Assert\IsNull($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert true.
 *
 * Validates that a value is true. Specifically, this checks to see if the
 * value is exactly true, exactly the integer 1, or exactly the string "1".
 *
 * Options:
 * - message: (optional) (string) (Default: 'This value should be true.')
 *   This message is shown if the underlying data is not true.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see validators_assert_is_false()
 */
function validators_assert_is_true($value, $options = array()) {
  $constraint = new Assert\IsTrue($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert false.
 *
 * Validates that a value is false. Specifically, this checks to see if the
 * value is exactly false, exactly the integer 0, or exactly the string "0".
 *
 * Options:
 * - message: (optional) (string) (Default: 'This value should be false.')
 *   This message is shown if the underlying data is not false.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see validators_assert_is_true()
 */
function validators_assert_is_false($value, $options = array()) {
  $constraint = new Assert\IsFalse($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert type.
 *
 * Validates that a value is of a specific data type. For example, if a
 * variable should be an array, you can use this constraint with the array
 * type option to validate this.
 *
 * Options:
 * - type (string): This required option is the fully qualified class name or
 *   one of the PHP datatypes as determined by PHP's is_ functions: array, bool,
 *   callable, float, double, int, integer, long, null, numeric, object, real,
 *   resource, scalar, string. Also, you can use ctype_ functions from
 *   corresponding built-in PHP extension. Consider a list of ctype functions:
 *   alnum, alpha, cntrl, digit, graph, lower, print, punct, space, upper,
 *   xdigit. Make sure that the proper locale is set before using one of
 *   these.
 * - message: (optional) (string) (Default: 'This value should be of type
 *   {{ type }}.') The message if the underlying data is not of the given type.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see http://php.net/manual/en/function.setlocale.php
 */
function validators_assert_type($value, $options = array()) {
  $constraint = new Assert\Type($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert valid e-mail address.
 *
 * Validates that a value is a valid email address. The underlying value is
 * cast to a string before being validated.
 *
 * Options:
 * - strict: (optional) (bool) (Default: false) When false, the email will be
 *   validated against a simple regular expression. If true, then the
 *   egulias/email-validator library is required to perform an RFC compliant
 *   validation.
 * - message: (optional) (string) (Default: This value is not a valid email
 *   address.) This message is shown if the underlying data is not a valid email
 *   address.
 * - checkMX: (optional) (bool) (Default: false) If true, then the checkdnsrr
 *   PHP function will be used to check the validity of the MX record of the
 *   host of the given email.
 * - checkHost: (optional) (bool) (Default: false) If true, then the checkdnsrr
 *   PHP function will be used to check the validity of the MX or the A or the
 *   AAAA record of the host of the given email.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see https://packagist.org/packages/egulias/email-validator
 * @see checkdnsrr()
 */
function validators_assert_email($value, $options = array()) {
  $constraint = new Assert\Email($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert length.
 *
 * Validates that a given string length is between some minimum and maximum
 * value.
 *
 * Options:
 * - min: (int) This required option is the "min" length value. Validation
 *   will fail if the given value's length is less than this min value.
 *   It is important to notice that NULL values and empty strings are
 *   considered valid no matter if the constraint required a minimum length.
 *   Validators are triggered only if the value is not blank.
 * - max: (int) This required option is the "max" length value. Validation will
 *   fail if the given value's length is greater than this max value.
 * - charset: (optional) (string) (Default: 'UTF-8') The charset to be used
 *   when computing value's length. The grapheme_strlen PHP function is used if
 *   available. If not, the mb_strlen PHP function is used if available. If
 *   neither are available, the strlen PHP function is used.
 * - minMessage: (optional) (string) (Default: 'This value is too short. It
 *   should have {{ limit }} characters or more.') The message that will be
 *   shown if the underlying value's length is less than the min option.
 * - maxMessage: (optional) (string) (Default: 'This value is too long. It
 *   should have {{ limit }} characters or less.') The message that will be
 *   shown if the underlying value's length is more than the max option.
 * - exactMessage: (optional) (string) (Default: 'This value should have exactly
 *   {{ limit }} characters.') The message that will be shown if min and max
 *   values are equal and the underlying value's length is not exactly this
 *   value.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see grapheme_strlen()
 * @see mb_strlen()
 * @see strlen()
 */
function validators_assert_length($value, $options = array()) {
  $constraint = new Assert\Length($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert valid URL.
 *
 * Validates that a value is a valid URL string.
 *
 * Options:
 * - message: (optional) (string) (Default: This value is not a valid URL.)
 *   This message is shown if the URL is invalid.
 * - protocols: (optional) (array) (Default: array('http', 'https'))
 *   The protocols considered to be valid for the URL. For example, if you
 *   also consider the ftp:// type URLs to be valid, redefine the protocols
 *   array, listing http, https, and also ftp.
 * - checkDNS: (optional) (bool) (Default: false)
 *   By default, this constraint just validates the syntax of the given URL.
 *   If you also need to check whether the associated host exists, set the
 *   checkDNS option to true. This option uses the checkdnsrr PHP function to
 *   check the validity of the ANY DNS record corresponding to the host
 *   associated with the given URL.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see checkdnsrr()
 */
function validators_assert_url($value, $options = array()) {
  $constraint = new Assert\Url($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert regex.
 *
 * Validates that a value matches a regular expression.
 *
 * Options
 * - pattern: (string) This required option is the regular expression pattern
 *   that the input will be matched against. By default, this validator will
 *   fail if the input string does not match this regular expression (via the
 *   preg_match PHP function). However, if match is set to false, then
 *   validation will fail if The input string does match this pattern.
 * - htmlPattern: (optional) (string) (Default: NULL) This option specifies the
 *   pattern to use in the HTML5 pattern attribute.
 *   You usually don't need to specify this option because by default, the
 *   constraint will convert the pattern given in the pattern option into an
 *   HTML5 compatible pattern. This means that the delimiters are removed
 *   (e.g. /[a-z]+/ becomes [a-z]+).
 *   However, there are some other incompatibilities between both patterns
 *   which cannot be fixed by the constraint. For instance, the HTML5 pattern
 *   attribute does not support flags. If you have a pattern like /[a-z]+/i,
 *   you need to specify the HTML5 compatible pattern in the htmlPattern option.
 *   Setting htmlPattern to false will disable client side validation.
 * - match: (optional) (bool) (Default: TRUE) If true (or not set), this
 *   validator will pass if the given string matches the given pattern regular
 *   expression. However, when this option is set to false, the opposite will
 *   occur: validation will pass only if The given string does not match the
 *   pattern regular expression.
 * - message: (optional) (string) (Default: 'This value is not valid.') This
 *   is the message that will be shown if this validator fails.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see preg_match()
 */
function validators_assert_regex($value, $options = array()) {
  $constraint = new Assert\Regex($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert valid IP.
 *
 * Validates that a value is a valid IP address. By default, this will
 * validate the value as IPv4, but a number of different options exist to
 * validate as IPv6 and many other combinations.
 *
 * Options:
 *   version (string) (Default: '4')
 *   This determines exactly how the IP address is validated and can take one
 *   of a variety of different values:
 *   All ranges
 *   4:   Validates for IPv4 addresses
 *   6:   Validates for IPv6 addresses
 *   All: Validates all IP formats
 *   No private ranges
 *   4_no_priv:   Validates for IPv4 but without private IP ranges
 *   6_no_priv:   Validates for IPv6 but without private IP ranges
 *   all_no_priv: Validates for all IP formats but without private IP ranges
 *   No reserved ranges
 *   4_no_res:   Validates for IPv4 but without reserved IP ranges
 *   6_no_res:   Validates for IPv6 but without reserved IP ranges
 *   all_no_res: Validates for all IP formats but without reserved IP ranges
 *   Only public ranges
 *   4_public:   Validates for IPv4 but without private and reserved ranges
 *   6_public:   Validates for IPv6 but without private and reserved ranges
 *   all_public: Validates for all IP formats but without private and
 *   reserved ranges
 * - message: (optional) (string) (Default: 'This is not a valid IP address.')
 *   This message is shown if the string is not a valid IP address.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 */
function validators_assert_ip($value, $options = array()) {
  $constraint = new Assert\Ip($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert valid UUID.
 *
 * Validates that a value is a valid Universally unique identifier (UUID) per
 * RFC 4122. By default, this will validate the format according to the RFC's
 * guidelines, but this can be relaxed to accept non-standard UUIDs that other
 * systems (like PostgreSQL) accept. UUID versions can also be restricted
 * using a whitelist.
 *
 * Options
 * - message: (optional) (string) (Default: 'This is not a valid UUID.')
 *   This message is shown if the string is not a valid UUID.
 * - strict: (optional) (boolean) (Default: TRUE) If this option is set to true
 *   the constraint will check if the UUID is formatted per the RFC's input
 *   format rules: 216fff40-98d9-11e3-a5e2-0800200c9a66.
 *   Setting this to false will allow alternate input formats like:
 *   - 216f-ff40-98d9-11e3-a5e2-0800-200c-9a66
 *   - {216fff40-98d9-11e3-a5e2-0800200c9a66}
 *   - 216fff4098d911e3a5e20800200c9a66
 * - versions: (optinal) (array) (Default: array(1, 2, 3, 4, 5) This option
 *   (array containing integers) can be used to only allow specific UUID
 *   versions. Valid versions are 1 - 5. The following PHP constants can also be
 *   used:
 *   - Uuid::V1_MAC
 *   - Uuid::V2_DCE
 *   - Uuid::V3_MD5
 *   - Uuid::V4_RANDOM
 *   - Uuid::V5_SHA1
 *   All five versions are allowed by default.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see http://en.wikipedia.org/wiki/Universally_unique_identifier
 * @see http://tools.ietf.org/html/rfc4122
 */
function validators_assert_uuid($value, $options = array()) {
  $constraint = new Assert\Uuid($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert range.
 *
 * Validates that a given number is between some minimum and maximum number.
 *
 * Options
 * - min: (int) This required option is the "min" value. Validation will fail if
 *   the given value is less than this min value.
 * - max: (int) This required option is the "max" value. Validation will fail if
 *   the given value is greater than this max value.
 * - minMessage: (optional) (string) (Default: 'This value should be {{ limit }}
 *   or more.') The message that will be shown if the underlying value is less
 *   than the min option.
 * - maxMessage: (optional) (string) (Default: 'This value should be {{ limit }}
 *   or less.') The message that will be shown if the underlying value is more
 *   than the max option.
 * - invalidMessage: (optional) (string) (Default: 'This value should be a valid
 *   number.')  The message that will be shown if the underlying value is not a
 *   number (per the is_numeric PHP function).
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see is_numeric()
 */
function validators_assert_range($value, $options = array()) {
  $constraint = new Assert\Range($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert equal.
 *
 * Validates that a value is equal to another value, defined in the options.
 * To force that a value is not equal, see
 * validators_assert_not_equal_to().
 *
 * Options
 * - value: (mixed) This option is required. It defines the value to compare to.
 *   It can be a string, number or object.
 * - message: (optional) (string) (Default: 'This value should be equal to
 *   {{ compared_value }}.') This
 *   is the message that will be shown if the value is not equal.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see validators_assert_not_equal_to()
 */
function validators_assert_equal_to($value, $options = array()) {
  $constraint = new Assert\EqualTo($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert not equal to.
 *
 * Validates that a value is not equal to another value, defined in the
 * options. To force that a value is equal, see
 * validators_assert_equal_to().
 *
 * Options
 * - value: (mixed) This option is required. It defines the value to compare to.
 *   It can be a string, number or object.
 * - message: (optional) (string) (Default: 'This value should not be equal to
 *   {{ compared_value }}.') This is the message that will be shown if the value
 *   is equal.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see validators_assert_equal_to()
 */
function validators_assert_not_equal_to($value, $options = array()) {
  $constraint = new Assert\NotEqualTo($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert identical.
 *
 * Validates that a value is identical to another value, defined in the
 * options. To force that a value is not identical, see
 * validators_assert_not_identical_to().
 *
 * Options
 * - value: (mixed) This option is required. It defines the value to compare to.
 *   It can be a string, number or object.
 * - message: (optional) (string) (Default: his value should be identical to
 *   {{ compared_value_type }} {{ compared_value }}.)
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see validators_assert_not_identical_to()
 */
function validators_assert_identical_to($value, $options = array()) {
  $constraint = new Assert\IdenticalTo($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert not identical.
 *
 * Validates that a value is not identical to another value, defined in the
 * options. To force that a value is identical, see
 * validators_assert_identical_to().
 *
 * Options
 * - value: (mixed) This option is required. It defines the value to compare to.
 *   It can be a string, number or object.
 * - message: (optional) (string) (Default: This value should not be identical
 *   to {{ compared_value_type }} {{ compared_value }}.) This is the message
 *   that will be shown if the value is not equal.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see validators_assert_identical_to()
 */
function validators_assert_not_identical_to($value, $options = array()) {
  $constraint = new Assert\NotIdenticalTo($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert les than.
 *
 * Validates that a value is less than another value, defined in the options.
 * To force that a value is less than or equal to another value,
 * see validators_assert_less_than_or_equal. To force a value is
 * greater than another value, see validators_assert_greater_than.
 *
 * Options
 * - value: (mixed) This option is required. It defines the value to compare to.
 *   It can be a string, number or object.
 * - message: (optional) (string) (Default: This value should be less than
 *   {{ compared_value }}.) This is the message that will be shown if the value
 *   is not less than the comparison value.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see validators_assert_less_than_or_equal()
 * @see validators_assert_greater_than()
 */
function validators_assert_less_than($value, $options = array()) {
  $constraint = new Assert\LessThan($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert less than or equal.
 *
 * Validates that a value is less than or equal to another value, defined in
 * the options. To force that a value is less than another value,
 * see validators_assert_less_than().
 *
 * Options
 * - value: (mixed) This option is required. It defines the value to compare to.
 *   It can be a string, number or object.
 * - message: (optional) (string) (Default: This value should be less than or
 *   equal to {{ compared_value }}.) This is the message that will be shown if
 *   the value is not less than or equal to the comparison value.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see validators_assert_less_than()
 */
function validators_assert_less_than_or_equal($value, $options = array()) {
  $constraint = new Assert\LessThanOrEqual($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert greater than.
 *
 * Validates that a value is greater than another value, defined in the
 * options. To force that a value is greater than or equal to another value,
 * see validators_assert_greater_than_or_equal(). To force a
 * value is less than another value, see
 * validators_assert_less_than().
 *
 * Options
 * - value: (mixed) This option is required. It defines the value to compare to.
 *   It can be a string, number or object.
 * - message: (optional) (string) (Default: This value should be greater than
 *   {{ compared_value }}.) This is the message that will be shown if the value
 *   is not greater than the comparison value.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see validators_assert_greater_than_or_equal()
 * @see validators_assert_less_than()
 */
function validators_assert_greater_than($value, $options = array()) {
  $constraint = new Assert\GreaterThan($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert greater than or equal.
 *
 * Validates that a value is greater than or equal to another value, defined
 * in the options. To force that a value is greater than another value, see
 * validators_assert_greater_than().
 *
 * Options
 * - value: (mixed) This option is required. It defines the value to compare to.
 *   It can be a string, number or object.
 * - message: (optional) (string) (Default: 'This value should be greater than
 *   or equal to {{ compared_value }}.') This is the message that will be shown
 *   if the value is not greater than or equal to the comparison value.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see validators_assert_greater_than()
 */
function validators_assert_greater_than_or_equal($value, $options = array()) {
  $constraint = new Assert\GreaterThanOrEqual($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Validates date.
 *
 * Validates that a value is a valid date, meaning either a DateTime object or
 * a string (or an object that can be cast into a string) that follows a valid
 * YYYY-MM-DD format.
 *
 * Options
 * - message: (optional) (string) (Default: 'This value is not a valid date.')
 *   This message is shown if the underlying data is not a valid date.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 */
function validators_assert_date($value, $options = array()) {
  $constraint = new Assert\Date($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert DateTime.
 *
 * Validates that a value is a valid "datetime", meaning either a DateTime
 * object or a string (or an object that can be cast into a string) that
 * follows a valid YYYY-MM-DD HH:MM:SS format.
 *
 * Options
 * - message: (optional) (string) (Default: 'This value is not a valid
 *   datetime.') This message is shown if the underlying data is not a valid
 *   datetime.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 */
function validators_assert_datetime($value, $options = array()) {
  $constraint = new Assert\DateTime($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert time.
 *
 * Validates that a value is a valid time, meaning either a DateTime object or
 * a string (or an object that can be cast into a string) that follows a valid
 * "HH:MM:SS" format.
 *
 * Options
 * - message: (optional) (string) (Default: 'This value is not a valid time.')
 *   This message is shown if the underlying data is not a valid time.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 */
function validators_assert_time($value, $options = array()) {
  $constraint = new Assert\Time($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert choice.
 *
 * This constraint is used to ensure that the given value is one of a given
 * set of valid choices. It can also be used to validate that each item in an
 * array of items is one of those valid choices.
 *
 * Options
 * - choices: (array) A required option (unless callback is specified) - this is
 *   the array of options that should be considered in the valid set. The input
 *   value will be matched against this array.
 * - callback: (string|array|Closure) This is a callback method that can be used
 *   instead of the choices option to return the choices array. See Supplying
 *   the Choices with a Callback Function for details on its usage.
 * - multiple: (optional) (bool) (Default: FALSE) If this option is true,
 *   the input value is expected to be an array instead of a single, scalar
 *   value. The constraint will check that each value of the input array can be
 *   found in the array of valid choices. If even one of the input values cannot
 *   be found, the validation will fail.
 * - min: (optional) (int) If the multiple option is true, then you can use the
 *   min option to force at least XX number of values to be selected. For
 *   example, if min is 3, but the input array only contains 2 valid items, the
 *   validation will fail.
 * - max: (optional) (int) If the multiple option is true, then you can use the
 *   max option to force no more than XX number of values to be selected. For
 *   example, if max is 3, but the input array contains 4 valid items, the
 *   validation will fail.
 * - message: (optional) (string) (Default: 'The value you selected is not a
 *   valid choice.') This is the message that you will receive if the multiple
 *   option is set to false and the underlying value is not in the valid array
 *   of choices.
 * - multipleMessage: (optional) (string) (Default: 'One or more of the given
 *   values is invalid.') This is the message that you will receive if the
 *   multiple option is set to true and one of the values on the underlying
 *   array being checked is not in the array of valid choices.
 * - minMessage: (optional) (string) (Default: 'You must select at least
 *   {{ limit }} choices.') This is the validation error message that's
 *   displayed when the user chooses too few choices per the min option.
 * - maxMessage: (optional) (string) (Default: 'You must select at most
 *   {{ limit }} choices.')  This is the validation error message that's
 *   displayed when the user chooses too many options per the max option.
 * - strict: (optional) (bool) (Default: FALSE) If true, the validator will also
 *   check the type of the input value. Specifically, this value is passed to as
 *   the third argument to the PHP in_array() method when checking to see if a
 *   value is in the valid choices array.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see http://symfony.com/doc/current/reference/constraints/Choice.html#supplying-the-choices-with-a-callback-function
 */
function validators_assert_choice($value, $options = array()) {
  $constraint = new Assert\Choice($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert collection.
 *
 * This constraint is used when the underlying data is a collection (i.e. an
 * array or an object that implements Traversable and ArrayAccess), but you'd
 * like to validate different keys of that collection in different ways. For
 * example, you might validate the email key using the Email constraint and the
 * inventory key of the collection with the Range constraint.
 * This constraint can also make sure that certain collection keys are present
 * and that extra keys are not present.
 *
 * Options
 * - fields: (array) This option is required and is an associative array
 *   defining all of the keys in the collection and, for each key, exactly
 *   which validator(s) should be executed against that element of the
 *   collection.
 * - allowExtraFields: (optional) (bool) (Default: FALSE) If this option is set
 *   to false and the underlying collection contains one or more elements that
 *   are not included in the fields option, a validation error will be
 *   returned. If set to true, extra fields are ok.
 * - extraFieldsMessage: (optional) (string) (Default: 'The fields {{ fields }}
 *   were not expected.') The message shown if allowExtraFields is false and an
 *   extra field is detected.
 * - allowMissingFields: (optional) (bool) (Default: FALSE) If this option is
 *   set to false and one or more fields from the fields option are not present
 *   in the underlying collection, a validation error will be returned. If set
 *   to true, it's ok if some fields in the fields option are not present in
 *   the underlying collection.
 * - missingFieldsMessage: (optional) (string) (Default: 'The fields
 *   {{ fields }} are missing.') The message shown if allowMissingFields is
 *   false and one or more fields are missing from the underlying collection.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 */
function validators_assert_collection($value, $options = array()) {
  $constraint = new Assert\Collection($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert count.
 *
 * Validates that a given collection's (i.e. an array or an object that
 * implements Countable) element count is between some minimum and maximum
 * value.
 *
 * Options
 * - min: (int) This required option is the "min" count value. Validation will
 *   fail if the given collection elements count is less than this min value.
 * - max: (int) This required option is the "max" count value. Validation will
 *   fail if the given collection elements count is greater than this max value.
 * - minMessage: (optional) (string) (Default: 'This collection should contain
 *   {{ limit }} elements or more.') The message that will be shown if the
 *   underlying collection elements count is less than the min option.
 * - maxMessage: (optional) (string) (Default: 'This collection should contain
 *   {{ limit }} elements or less.') The message that will be shown if the
 *   underlying collection elements count is more than the max option.
 * - exactMessage: (optional) (string) (Default: 'This collection should
 *   contain exactly {{ limit }} elements.') The message that will be shown if
 *   min and max values are equal and the underlying collection elements count
 *   is not exactly this value.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 */
function validators_assert_count($value, $options = array()) {
  $constraint = new Assert\Count($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert language.
 *
 * Validates that a value is a valid language Unicode language identifier (e.g.
 * fr or zh-Hant).
 *
 * Options
 * - message: (optional) (string) (Default: 'This value is not a valid
 *   language.') This message is shown if the string is not a valid language
 *   code.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 */
function validators_assert_language($value, $options = array()) {
  $constraint = new Assert\Language($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert locale.
 *
 * Validates that a value is a valid locale.
 * The "value" for each locale is either the two letter ISO 639-1 language code
 * (e.g. fr), or the language code followed by an underscore (_), then the ISO
 * 3166-1 alpha-2 country code (e.g. fr_FR for French/France).
 *
 * Options
 * - message: (optional) (string) (Default: 'This value is not a valid locale.')
 *   This message is shown if the string is not a valid locale.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes
 * @see https://en.wikipedia.org/wiki/ISO_3166-1#Current_codes
 */
function validators_assert_locale($value, $options = array()) {
  $constraint = new Assert\Locale($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert country.
 *
 * Validates that a value is a valid ISO 3166-1 alpha-2 country code.
 *
 * Options
 * - message: (optional) (string) (Default: 'This value is not a valid
 *   country.') This message is shown if the string is not a valid country code.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see https://en.wikipedia.org/wiki/ISO_3166-1#Current_codes
 */
function validators_assert_country($value, $options = array()) {
  $constraint = new Assert\Country($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert file.
 *
 * Validates that a value is a valid "file", which can be one of the following:
 * - A string (or object with a __toString() method) path to an existing file;
 * - A valid File object (including objects of class UploadedFile).
 *
 * Options
 * - maxSize: (optional) (mixed) If set, the size of the underlying file must
 *   be below this file size in order to be valid. The size of the file can be
 *   given in one of the following formats:
 *   Suffix Unit Name value           e.g.
 *          byte      1 byte          4096
 *   k      kilobyte  1,000 bytes     200k
 *   M      megabyte  1,000,000 bytes 2M
 *   Ki     kibibyte  1,024 bytes     32Ki
 *   Mi     mebibyte  1,048,576 bytes 8Mi
 *   For more information about the difference between binary and SI prefixes,
 *   see Wikipedia: Binary prefix.
 * - binaryFormat: (optional) (bool) (Default: NULL) When true, the sizes will
 *   be displayed in messages with binary-prefixed units (KiB, MiB). When
 *   false, the sizes will be displayed with SI-prefixed units (kB, MB). When
 *   null, then the binaryFormat will be guessed from the value defined in the
 *   maxSize option. For more information about the difference between binary
 *   and SI prefixes, see Wikipedia: Binary prefix.
 * - mimeTypes: (optional) (array|string) If set, the validator will check that
 *   the mime type of the underlying file is equal to the given mime type (if
 *   a string) or exists in the collection of given mime types (if an array).
 *   You can find a list of existing mime types on the IANA website.
 * - maxSizeMessage: (optional) (string) (Default: 'The file is too large
 *   ({{ size }} {{ suffix }}). Allowed maximum size is {{ limit }}
 *   {{ suffix }}.') The message displayed if the file is larger than the
 *   maxSize option.
 * - mimeTypesMessage: (optional) (string) (Default: 'The mime type of the file
 *   is invalid ({{ type }}). Allowed mime types are {{ types }}.') The message
 *   displayed if the mime type of the file is not a valid mime type per the
 *   mimeTypes option.
 * - disallowEmptyMessage: (optional) (string) (Default: 'An empty file is not
 *   allowed.') This constraint checks if the uploaded file is empty (i.e. 0
 *   bytes). If it is, this message is displayed.
 * - notFoundMessage: (optional) (string) (Default: 'The file could not be
 *   found.') The message displayed if no file can be found at the given path.
 *   This error is only likely if the underlying value is a string path, as a
 *   File object cannot be constructed with an invalid file path.
 * - notReadableMessage: (optional) (string) (Default: 'The file is not
 *   readable.') The message displayed if the file exists, but the PHP
 *   is_readable function fails when passed the path to the file.
 * - uploadIniSizeErrorMessage: (optional) (string) (Default: 'The file is too
 *   large. Allowed maximum size is {{ limit }} {{ suffix }}.')
 * - uploadFormSizeErrorMessage: (optional) (string) (Default: 'The file is too
 *   large.') The message that is displayed if the uploaded file is larger than
 *   allowed by the HTML file input field.
 * - uploadErrorMessage: (optional) (string) (Default: The file could not be
 *   uploaded.) The message that is displayed if the uploaded file could not be
 *   uploaded for some unknown reason, such as the file upload failed or it
 *   couldn't be written to disk.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see http://en.wikipedia.org/wiki/Binary_prefix
 * @see http://www.iana.org/assignments/media-types/index.html
 */
function validators_assert_file($value, $options = array()) {
  $constraint = new Assert\File($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert image.
 *
 * The Image constraint works exactly like the File constraint, except that its
 * mimeTypes and mimeTypesMessage options are automatically setup to work for
 * image files specifically.
 * Additionally it has options so you can validate against the width and
 * height of the image.
 *
 * Options
 * - mimeTypes: (optional) (array|string) (Default: image/*) You can find a
 *   list of existing image mime types on the IANA website.
 * - mimeTypesMessage: (optional) (string) (Default: 'This file is not a valid
 *   image.')
 * - minWidth: (optional) (int) If set, the width of the image file must be
 *   greater than or equal to this value in pixels.
 * - maxWidth: (optional) (int) If set, the width of the image file must be
 *   less than or equal to this value in pixels.
 * - minHeight: (optional) (int) If set, the height of the image file must be
 *   greater than or equal to this value in pixels.
 * - maxHeight: (optional) (int) If set, the height of the image file must be
 *   less than or equal to this value in pixels.
 * - maxRatio: (optional) (float) If set, the aspect ratio (width / height) of
 *   the image file must be less than or equal to this value.
 * - minRatio: (optional) (float) If set, the aspect ratio (width / height) of
 *   the image file must be greater than or equal to this value.
 * - allowSquare: (optional) (bool) (Default: TRUE) If this option is false,
 *   the image cannot be a square. If you want to force a square image, then
 *   set leave this option as its default true value and set allowLandscape and
 *   allowPortrait both to false.
 * - allowLandscape: (optional) (bool) (Default: TRUE) If this option is false,
 *   the image cannot be landscape oriented.
 * - allowPortrait: (optional) (bool) (Default: TRUE) If this option is false,
 *   the image cannot be portrait oriented.
 * - sizeNotDetectedMessage: (optional) (string) (Default: 'The size of the
 *   image could not be detected.') If the system is unable to determine the
 *   size of the image, this error will be displayed. This will only occur when
 *   at least one of the size constraint options has been set.
 * - maxWidthMessage: (optional) (string) (Default: 'The image width is too big
 *   ({{ width }}px). Allowed maximum width is {{ max_width }}px.') The error
 *   message if the width of the image exceeds maxWidth.
 * - minWidthMessage: (optional) (string) (Default: 'The image width is too
 *   small ({{ width }}px). Minimum width expected is {{ min_width }}px.') The
 *   error message if the width of the image is less than minWidth.
 * - maxHeightMessage: (optional) (string) (Default: 'The image height is too
 *   big ({{ height }}px). Allowed maximum height is {{ max_height }}px.')
 *   The error message if the height of the image exceeds maxHeight.
 * - minHeightMessage: (optional) (string) (Default: 'The image height is too
 *   small ({{ height }}px). Minimum height expected is {{ min_height }}px.')
 *   The error message if the height of the image is less than minHeight.
 * - maxRatioMessage: (optional) (string) (Default: 'The image ratio is too big
 *   ({{ ratio }}). Allowed maximum ratio is {{ max_ratio }}') The error
 *   message if the aspect ratio of the image exceeds maxRatio.
 * - minRatioMessage: (optional) (string) (Default: 'The image ratio is too
 *   small ({{ ratio }}). Minimum ratio expected is {{ min_ratio }}') The error
 *   message if the aspect ratio of the image is less than minRatio.
 * - allowSquareMessage: (optional) (string) (Default: 'The image is square
 *   ({{ width }}x{{ height }}px). Square images are not allowed') The error
 *   message if the image is square and you set allowSquare to false.
 * - allowLandscapeMessage: (optional) (string) (Default: ' The image is
 *   landscape oriented ({{ width }}x{{ height }}px). Landscape oriented images
 *   are not allowed') The error message if the image is landscape oriented
 *   and you set allowLandscape to false.
 * - allowPortraitMessage: (optional) (string) (Default: 'The image is portrait
 *   oriented ({{ width }}x{{ height }}px). Portrait oriented images are not
 *   allowed') The error message if the image is portrait oriented and you set
 *   allowPortrait to false.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see http://www.iana.org/assignments/media-types/image/index.html
 */
function validators_assert_image($value, $options = array()) {
  $constraint = new Assert\Image($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert card scheme.
 *
 * This constraint ensures that a credit card number is valid for a given
 * credit card company. It can be used to validate the number before trying to
 * initiate a payment through a payment gateway.
 *
 * Options
 * - schemes: (mixed) This option is required and represents the name of the
 *   number scheme used to validate the credit card number, it can either be a
 *   string or an array. Valid values are: AMEX, CHINA_UNIONPAY, DINERS,
 *   DISCOVER, INSTAPAYMENT JCB, LASER, MAESTRO, MASTERCARD, VISA.
 *   For more information about the used schemes, see Wikipedia: Issuer
 *   identification number (IIN).
 * - message: (optional) (string) (Default: 'Unsupported card type or invalid
 *   card number.') The message shown when the value does not pass the
 *   CardScheme check.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see https://en.wikipedia.org/wiki/Bank_card_number#Issuer_identification_number_.28IIN.29
 */
function validators_assert_card_scheme($value, $options = array()) {
  $constraint = new Assert\CardScheme($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert currency.
 *
 * Validates that a value is a valid 3-letter ISO 4217 currency name.
 *
 * Options
 * - message: (optional) (string) (Default: 'This value is not a valid
 *   currency.')
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see https://en.wikipedia.org/wiki/ISO_4217
 */
function validators_assert_currency($value, $options = array()) {
  $constraint = new Assert\Currency($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert luhn.
 *
 * This constraint is used to ensure that a credit card number passes the Luhn
 * algorithm. It is useful as a first step to validating a credit card: before
 * communicating with a payment gateway.
 *
 * Options
 * - message: (optional) (string) (Default: ' Invalid card number.') The
 *   default message supplied when the value does not pass the Luhn check.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see https://en.wikipedia.org/wiki/Luhn_algorithm
 */
function validators_assert_luhn($value, $options = array()) {
  $constraint = new Assert\Luhn($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert iban.
 *
 * This constraint is used to ensure that a bank account number has the proper
 * format of an International Bank Account Number (IBAN). IBAN is an
 * internationally agreed means of identifying bank accounts across national
 * borders with a reduced risk of propagating transcription errors.
 *
 * Options
 * - message: (optional) (string) (Default: 'This is not a valid International
 *   Bank Account Number (IBAN).') The default message supplied when the value
 *   does not pass the Iban check.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see https://en.wikipedia.org/wiki/International_Bank_Account_Number
 */
function validators_assert_iban($value, $options = array()) {
  $constraint = new Assert\Iban($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert isbn.
 *
 * This constraint validates that an International Standard Book Number (ISBN)
 * is either a valid ISBN-10 or a valid ISBN-13.
 * Notice: The isbn10 and isbn13 options are deprecated since Symfony 2.5 and
 * will be removed in Symfony 3.0. Use the type option instead. Furthermore,
 * when using the type option, lowercase characters are no longer supported
 * starting in Symfony 2.5, as they are not allowed in ISBNs.
 *
 * Options
 * - type: (optional) (string) (Default: NULL) The type of ISBN to validate
 *   against. Valid values are isbn10, isbn13 and null to accept any kind of
 *   ISBN.
 * - message: (optional) (string) (Default: NULL) The message that will be
 *   shown if the value is not valid. If not null, this message has priority
 *   over all the other messages.
 * - isbn10Message: (optional) (string) (Default: 'This value is not a valid
 *   ISBN-10.') The message that will be shown if the type option is isbn10
 *   and the given value does not pass the ISBN-10 check
 * - isbn13Message: (optional) (string) (Default: 'This value is not a valid
 *   ISBN-13.') The message that will be shown if the type option is isbn13 and
 *   the given value does not pass the ISBN-13 check.
 * - bothIsbnMessage: (optional) (string) (Default: 'This value is neither a
 *   valid ISBN-10 nor a valid ISBN-13.') The message that will be shown if the
 *   type option is null and the given value does not pass any of the ISBN
 *   checks.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see https://en.wikipedia.org/wiki/Isbn
 */
function validators_assert_isbn($value, $options = array()) {
  $constraint = new Assert\Isbn($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert issn.
 *
 * Validates that a value is a valid International Standard Serial Number
 * (ISSN).
 *
 * Options
 * - message: (optional) (string) (Default: 'This value is not a valid ISSN.')
 *   The message shown if the given value is not a valid ISSN.
 * - caseSensitive: (optional) (bool) (Default: FALSE) The validator will
 *   allow ISSN values to end with a lower case 'x' by default. When switching
 *   this to true, the validator requires an upper case 'X'.
 * - requireHyphen: (optional) (bool) (Default: FALSE) The validator will
 *   allow non hyphenated ISSN values by default. When switching this to true,
 *   the validator requires a hyphenated ISSN value.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see https://en.wikipedia.org/wiki/Issn
 */
function validators_assert_issn($value, $options = array()) {
  $constraint = new Assert\Issn($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert callback.
 *
 * The purpose of the Callback constraint is to create completely custom
 * validation rules and to assign any validation errors to specific fields on
 * your object. If you're using validation with forms, this means that you can
 * make these custom errors display next to a specific field, instead of simply
 * at the top of your form.
 * This process works by specifying one or more callback methods, each of
 * which will be called during the validation process. Each of those methods
 * can do anything, including creating and assigning validation errors.
 *
 * Options
 * - callback: (string|array|Closure) The callback option accepts three
 *   different formats for specifying the callback method:
 *   - A string containing the name of a concrete or static method;
 *   - An array callable with the format array('<Class>', '<method>');
 *   - A closure.
 *   Concrete callbacks receive an ExecutionContextInterface instance as only
 *   argument.
 *   Static or closure callbacks receive the validated object as the first
 *   argument and the ExecutionContextInterface instance as the second argument.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 *
 * @see http://symfony.com/doc/current/reference/constraints/Callback.html
 */
function validators_assert_callback($value, $options = array()) {
  $constraint = new Assert\Callback($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert expression.
 *
 * This constraint allows you to use an expression for more complex, dynamic
 * validation. See Basic Usage for an example. See Callback for a different
 * constraint that gives you similar flexibility.
 *
 * Options
 * - expression: (string) The expression that will be evaluated. If the
 *   expression evaluates to a false value (using ==, not ===), validation
 *   will fail. To learn more about the expression language syntax, see The
 *   Expression Syntax.
 *   Inside of the expression, you have access to up to 2 variables:
 *   Depending on how you use the constraint, you have access to 1 or 2
 *   variables in your expression:
 *   - this: The object being validated (e.g. an instance of BlogPost);
 *   - value: The value of the property being validated (only available when
 *            the constraint is applied directly to a property);
 * - message: (optional) (string) (Default: 'This value is not valid.')
 *   The default message supplied when the expression evaluates to false.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 */
function validators_assert_expression($value, $options = array()) {
  $constraint = new Assert\Expression($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert all.
 *
 * When applied to an array (or Traversable object), this constraint allows you
 * to apply a collection of constraints to each element of the array.
 *
 * Options
 * - constraints: (array) This required option is the array of validation
 *   constraints that you want to apply to each element of the underlying array.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 */
function validators_assert_all($value, $options = array()) {
  $constraint = new Assert\All($options);
  return _validators_process_validation($value, $constraint);
}

/**
 * Assert valid.
 *
 * This constraint is used to enable validation on objects that are embedded as
 * properties on an object being validated. This allows you to validate an
 * object and all sub-objects associated with it.
 *
 * Options
 * - traverse: (optional) (bool) (Default: TRUE) If this constraint is applied
 *   to a property that holds an array of objects, then each object in that
 *   array will be validated only if this option is set to true.
 * - deep: (optional) (bool) (Default: FALSE) If this constraint is applied to
 *   a property that holds an array of objects, then each object in that array
 *   will be validated recursively if this option is set to true.
 *
 * @param string $value
 *   The value that needs to be checked.
 * @param array $options
 *   An array containing the options for the constraint.
 *
 * @return array
 *   Returns an array containing the violation messages. If there are no
 *   violations, an empty array will be returned.
 */
function validators_assert_valid($value, $options = array()) {
  $constraint = new Assert\Valid($options);
  return _validators_process_validation($value, $constraint);
}
