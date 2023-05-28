#/bin/bash

function color(){
	local color=$2
	if [ $color == "black" ]; then
		echo -e "\e[30m${1}\e[0m"

	elif [ $color == "yellow" ]; then
		echo -e "\e[33m${1}\e[0m"

	elif [ $color == "magenta" ]; then
		echo -e "\e[35m${1}\e[0m"

	elif [ $color == "cyan" ]; then
		echo -e "\e[36m${1}\e[0m"

	elif [ $color == "white" ]; then
		echo -e "\e[97m${1}\e[0m"
	else
		echo "Podałeś kolor spoza zakresu wyboru."
	fi
}

color $1 $2
