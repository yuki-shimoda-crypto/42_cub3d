#!/bin/bash

# Directions array
directions=("over_255" "over_int_max" "over_long_max" "under_0" "under_int_min" "under_long_min")

# Loop from 09 to 14
for i in {0..5}
do
    # Using 'expr' to add leading zero to single digit numbers
    num=$(expr $i + 21)
    num=$(printf "%02d" $num)

    cp "valid_01_subject.cub" "invalid_${num}_${directions[$i]}.cub"
done

