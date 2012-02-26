#!/bin/bash
clear
premake4 vs2010  2> /dev/null >/dev/null
premake4 gmake 2> /dev/null > /dev/null
make 2>&1 | grep -m1 error

