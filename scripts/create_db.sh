#!/bin/bash

#echo "Creating database. MySQL root password needed"
#mysql -u root -p -e "CREATE DATABASE timekeeper;"
#mysql timekeeper -u root -p -e "GRANT ALL PRIVILEGES ON timekeeper
#	TO 'timekeeperApp'@localhost IDENTIFIED BY 'securepasswd';
#	FLUSH PRIVILEGES;"
#echo "Database created"

echo "Creating data tables and populating with test entries."
mysql timekeeper -u timekeeperApp -p securepasswd < initialize.sql
