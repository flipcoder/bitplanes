#!/bin/bash

rm bin/bitplanes
pushd build > /dev/null
cmake . > /dev/null
make 2>&1
popd
