#!/bin/bash
for var in pointA.c pointB.c pointC.c
do
  echo "!pynkt $var"
  gcc $var -o sss && ./sss && rm sss
done
