#!/bin/bash

SENTENCE="i saw a girl with a telescope"

make clean
make

echo "$SENTENCE" | ./main
