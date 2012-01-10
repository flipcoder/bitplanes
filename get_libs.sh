#!/bin/bash

echo This script will use \`apt-get\` and wget to obtain the packages necessary for development.
echo Press a key...
read

sudo apt-get install `cat third_party/lib_names.txt`

echo Done! Press a key to exit...
read

