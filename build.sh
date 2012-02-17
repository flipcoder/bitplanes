#!/bin/bash

rm bin/bitplanes
premake4 gmake
pushd build > /dev/null
#cmake . > /dev/null
make 2>&1
popd

