#!/bin/bash

rm bin/bitplanes

premake4 vs2010
premake4 gmake

make 2>&1

