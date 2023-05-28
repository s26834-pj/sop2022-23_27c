#!/bin/bash

echo "Podaj kod:"
read kod

if [[ $kod =~ ^[0-9]{2}-?[0-9]{3}$ ]]; then
    echo "To jest poprawny kod."
else
    echo "Niepoprawny kod."
fi
