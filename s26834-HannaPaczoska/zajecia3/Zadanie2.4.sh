#!/bin/bash

for file in *.c
do
  if [[ "${file##*.}" == "c" ]]; then 
  filename=$(basename "$file")
  filename="${filename%.*}"
  cc "$file" -o "$filename"
  fi
done
