#!/bin/bash
clear
premake4 gmake . 2> /dev/null > /dev/null
pushd build > /dev/null
make 2>&1 | grep -m1 error
popd > /dev/null
