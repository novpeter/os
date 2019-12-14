#!/bin/bash

user=$1
catalog=$2
filename=$3
files=()

open_dir() {
    dir=$1
    for file in $dir/*
    do
        if [ -d $file ]; then
            open_dir $file
        else
            files+=($file)
        fi
    done
}

open_dir $2

echo ${#files[@]}

delimiter=" "

for temp in ${files[@]}
do
    array=()
    s=$(ls -lah $temp)$delimiter
    
    while [[ $s ]]; do
        str=${s%%"$delimiter"*}
        if [[ $str != "" ]]; then array+=( $str ); fi
        s=${s#*"$delimiter"};
    done
    
    if [[ ${array[2]} == $user ]]; then echo "$(pwd $temp) $(basename $temp) ${array[4]}" >> $filename; fi
done

exit 0
