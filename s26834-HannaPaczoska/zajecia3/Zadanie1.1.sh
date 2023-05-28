#!/bin/bash

if [ $# -gt 1 ]; then
  echo "Parametr: $1"
elif [ $# -eq 1 ]; then
  echo "Podano jeden parametr."
  echo "Wartość: $1"
else
  echo "Nie podano parametrów."
fi
