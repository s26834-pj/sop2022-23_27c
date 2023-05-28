#!/bin/bash

# Funkcja do wypisywania zawartości pliku od początku do końca
print_file() {
  while IFS= read -r line; do
    echo "$line"
  done < "$1"
}

# Funkcja do wypisywania zawartości pliku od końca do początku
print_file_reverse() {
  lines=()
  while IFS= read -r line; do
    lines=("$line" "${lines[@]}")
  done < "$1"
  
  for line in "${lines[@]}"; do
    echo "$line"
  done
}

# Wczytanie listy plików z argumentów wiersza poleceń
files=("$@")

# Wypisanie zawartości plików od początku do końca
for file in "${files[@]}"; do
  echo "Zawartość: $file (od początku do końca)"
  print_file "$file"
  echo
done

# Wypisanie zawartości plików od końca do początku
for file in "${files[@]}"; do
  echo "Zawartość: $file (od końca do początku)"
  print_file_reverse "$file"
  echo
done
