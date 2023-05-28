#!/bin/bash

config="config.cfg"

if [ -f "$config" ]; then
  echo "Wykonuję plik $config"
  source "$config"
elif [ $# -eq 1 ]; then
  script="$1"
  if [ -f "$script" ]; then
    echo "Wykonuję plik $script"
    source "$script"
  else
    echo "Błąd: Plik $script nie istnieje."
  fi
else
  echo "Błąd: Brak pliku config.cfg i nie podano argumentu."
fi
