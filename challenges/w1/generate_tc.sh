#!/bin/bash

echo 75000 75000
cat /dev/urandom | tr -c -d '[a-z]' | head -c 75000
echo
for f in {1..75000};
do
    idx=$((RANDOM%75000))
    ch=b
    echo ${idx} ${ch}
done
