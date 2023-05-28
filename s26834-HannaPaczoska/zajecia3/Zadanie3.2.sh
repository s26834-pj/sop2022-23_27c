#!/bin/bash

# Funkcja rekurencyjna obliczająca ciąg Fibonacciego
fibonacci() {
  local n=$1

  if [ "$n" -le 0 ]; then
    return 0
  elif [ "$n" -eq 1 ]; then
    return 1
  else
    local fib1
    local fib2
    fibonacci "$((n-1))"
    fib1=$?
    fibonacci "$((n-2))"
    fib2=$?
    return "$((fib1 + fib2))"
  fi
}

# Przykładowe użycie funkcji
fibonacci 4
result=$?
exit $result
 
