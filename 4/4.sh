#!/bin/bash

echo -n > 4_output.txt

for arg in $@
do
    echo $arg
    echo $arg >> 4_output.txt
done

exit 0
