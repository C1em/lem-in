#!/bin/bash

RES=$(./generator --big-superposition > map && .././lem-in < map > out && ./verifier < out | wc -l)
while [ $RES -eq  1 ]
do
RES=$(./generator --big-superposition > map && .././lem-in < map > out && ./verifier < out | wc -l)
done
echo $RES
