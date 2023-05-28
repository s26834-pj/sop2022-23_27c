#!/bin/bash

if [ ${1:(-1)} = 'a' ]; then
echo "$1 ma kota, a kot ma ${1/%a/ę}"
else
echo  "$1 ma kota, a kot ma $1a"

fi

