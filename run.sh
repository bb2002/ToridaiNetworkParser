#!/bin/bash

SENTENCE="fruit flies like an apple"

make clean
make

echo "$SENTENCE" | ./main
