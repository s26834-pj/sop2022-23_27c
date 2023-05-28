#!/bin/bash

script_name="${0##*/}" 


if [[ ! "$script_name" =~ \.sh$ ]]; then
  echo "Zmieniam nazwę skryptu przez dopisanie rozszerzenia .sh"
  mv "$script_name" "${script_name}.sh"
  script_name="${script_name}.sh"
fi

if [[ "${script_name: -3}" != ".sh" ]]; then
  echo "Zmieniam nazwę skryptu przez dopisanie rozszerzenia .sh"
  mv "$script_name" "${script_name}.sh"
  script_name="${script_name}.sh"
fi


if [[ "${script_name%.*}" != "$script_name" ]]; then
  echo "Zmieniam nazwę skryptu przez dopisanie rozszerzenia .sh"
  mv "$script_name" "${script_name%.*}.sh"
  script_name="${script_name%.*}.sh"
fi

echo "Nazwa skryptu: $script_name"
