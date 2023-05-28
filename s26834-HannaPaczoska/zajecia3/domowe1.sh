#!/bin/bash

echo "Podaj imię:"
read imie

if [[ $imie =~ ^[A-ZĄĆĘŁŃÓŚŹŻ][a-ząćęłńóśźż]+$ ]]; then
    echo "Poprawne imię."
else
    echo "Niepoprawne imię."
fi
