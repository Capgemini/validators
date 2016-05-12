#!/bin/bash

# Add an optional statement to see that this is running in Travis CI.
echo "running drupal_ti/before/before_script.sh"

set -e $DRUPAL_TI_DEBUG

# Ensure the right Drupal version is installed.
# The first time this is run, it will install Drupal.
# Note: This function is re-entrant.
drupal_ti_ensure_drupal

# Change to the Drupal directory
cd "$DRUPAL_TI_DRUPAL_DIR"

# Create the the module directory (only necessary for D7)
# For D7, this is sites/default/modules
# For D8, this is modules
mkdir -p "$DRUPAL_TI_DRUPAL_DIR/$DRUPAL_TI_MODULES_PATH"
cd "$DRUPAL_TI_DRUPAL_DIR/$DRUPAL_TI_MODULES_PATH"

# Manually clone the dependencies
git clone --depth 1 --branch 7.x-1.x http://git.drupal.org/project/composer_manager.git

# Initialize composer manage
php "$DRUPAL_TI_DRUPAL_DIR/$DRUPAL_TI_MODULES_PATH/composer_manager/scripts/init.php"

# Ensure the module is linked into the code base and enabled.
# Note: This function is re-entrant.
drupal_ti_ensure_module_linked

# Update composer
cd "$DRUPAL_TI_DRUPAL_DIR"
composer drupal-rebuild
composer install --prefer-source

set -e $DRUPAL_TI_DEBUG

# Require that minimal profile enables decoupled_auth.
ls $DRUPAL_TI_DRUPAL_DIR
ls $DRUPAL_TI_DRUPAL_DIR/modules/validators
#cp $DRUPAL_TI_DRUPAL_DIR/modules/validators/travis-ci/minimal.info.yml $DRUPAL_TI_DRUPAL_DIR/core/profiles/minimal

# Enable main module and submodules.
drush en -y validators