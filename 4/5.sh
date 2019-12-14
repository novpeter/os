#!/bin/bash

filename=$1
catalog=$2
extension=$3

echo -n > filename

for f in $catalog/*
do
    file=$(basename "$f")
    ext="${file##*.}"

    if [[ $extension == $ext ]]
    then
        echo $f
        echo $f >> $filename
    fi
    
done

exit 0