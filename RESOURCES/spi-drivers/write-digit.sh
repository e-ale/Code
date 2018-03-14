#!/bin/bash

for i in $(seq 496 1 511)
do
        if [[ ! -d "/sys/class/gpio/gpio$i" ]]
        then
                echo "$i" > /sys/class/gpio/export
        fi
done
 
getbits () {
	case $1 in
        	0) bits="0 1 1 1 1 1 1" ;;
        	1) bits="0 0 0 0 1 1 0" ;;
        	2) bits="1 0 1 1 0 1 1" ;;
        	3) bits="1 0 0 1 1 1 1" ;;
        	4) bits="1 1 0 0 1 1 0" ;;
        	5) bits="1 1 0 1 1 0 1" ;;
        	6) bits="1 1 1 1 1 0 1" ;;
        	7) bits="0 0 0 0 1 1 1" ;;
        	8) bits="1 1 1 1 1 1 1" ;;
        	9) bits="1 1 0 1 1 1 1" ;;
        	a) bits="1 1 1 0 1 1 1" ;;
        	b) bits="1 1 1 1 1 0 0" ;;
        	c) bits="0 1 1 1 0 0 1" ;;
        	d) bits="1 0 1 1 1 1 0" ;;
        	e) bits="1 1 1 1 0 0 1" ;;
        	f) bits="1 1 1 0 0 0 1" ;;
        	g) bits="0 0 0 0 0 0 0" ;;
        	h) bits="1 0 1 0 1 0 1" ;;
        	i) bits="0 1 0 1 0 1 0" ;;
        	_) bits="0 0 0 0 0 0 0" ;;
	esac
 	
	echo "$bits"
}
bits=$(getbits "$2")
i=510
 
for j in $bits
do
        if [[ $j == "1" ]]
        then
                echo out > /sys/class/gpio/gpio$i/direction
        else
                echo in > /sys/class/gpio/gpio$i/direction
        fi
        i=$((i-1))
done
 
bits=$(getbits "$1")
i=502
 
for j in $bits
do
        if [[ $j == "1" ]]
        then
                echo out > /sys/class/gpio/gpio$i/direction
        else
                echo in > /sys/class/gpio/gpio$i/direction
        fi
        i=$((i-1))
done
