#!/bin/bash

# Directions array
directions=("NORTH" "SOUTH" "EAST" "WEST" "F" "C")

# Loop from 09 to 14
for i in {0..5}
do
    # Using 'expr' to add leading zero to single digit numbers
    num=$(expr $i + 9)
    num=$(printf "%02d" $num)

    cp "valid_01_subject.cub" "invalid_${num}_more_than_one_${directions[$i]}.cub"
done

