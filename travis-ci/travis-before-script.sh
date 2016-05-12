#!/bin/bash

# Add an optional statement to see that this is running in Travis CI.
echo "running drupal_ti/before/before_script.sh"

set -e $DRUPAL_TI_DEBUG

# Ensure the right Drupal version is installed.
# The first time this is run, it will install Drupal.
# Note: This function is re-entrant.
drupal_ti_ensure_drupal
git clone --branch 8.x-1.x http://git.drupal.org/project/composer.git /home/travis/.drush/composer

# Change to the Drupal directory
cd "$DRUPAL_TI_DRUPAL_DIR"

# Create the the module directory (only necessary for D7)
# For D7, this is sites/default/modules
# For D8, this is modules
mkdir -p "/home/travis/build/Capgemini/drupal-7/drupal/sites/all/modules/"
cd "/home/travis/build/Capgemini/drupal-7/drupal/sites/all/modules/"

# Manually clone the dependencies
git clone --depth 1 --branch 7.x-1.x http://git.drupal.org/project/composer_manager.git

# Ensure the module is linked into the code base and enabled.
# Note: This function is re-entrant.
drupal_ti_ensure_module_linked

# Update composer
cd "/home/travis/build/Capgemini/drupal-7/drupal"
drush dl composer_manager --yes
drush pm-enable composer_manager --yes

set -e $DRUPAL_TI_DEBUG

drush cc all
drush en -y validators