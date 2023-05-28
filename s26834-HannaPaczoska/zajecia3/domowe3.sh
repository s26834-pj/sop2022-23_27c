#!/bin/bash

echo "Podaj e-mail:"
read email

if [[ $email =~ ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$ ]]; then
    echo "To jest poprawny adres e-mail."
else
    echo "Niepoprawny adres e-mail."
fi
