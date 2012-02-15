#!/bin/bash
clear
pushd build > /dev/null
cmake . 2> /dev/null > /dev/null
make 2>&1 | grep -m1 error
popd > /dev/null
