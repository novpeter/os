#!/bin/bash

file=$1
exe_file=$2

$(gcc $file -o ./$exe_file)
if [ -f "./$file" ]; then
    $(chmod +x ./$exe_file)
    echo $(./$exe_file)
else 
    exit 1
fi
