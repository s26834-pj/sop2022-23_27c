#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "Użycie: $0 <argument>"
    exit 1
fi

argument=$1

if [[ $argument =~ ^[A-ZĄĆĘŁŃÓŚŹŻ][a-ząćęłńóśźż]+$ ]]; then
    echo "imię"
elif [[ $argument =~ ^[0-9]{2}-?[0-9]{3}$ ]]; then
    echo "kod"
elif [[ $argument =~ ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$ ]]; then
    echo "email"
else
    echo "Nieznany format"
fi

