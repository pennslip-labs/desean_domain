#!/bin/bash

#author: Shamar Pennant
#date: 08/02/26

# Takes .cpp files as arguments, last argument is the output file name
# Compiles with wxWidgets in mind

OUTPUT=${@: -1}  # Get last argument as output file
FILES=${@:1:$#-1}  # Get all arguments except the last one as input files

echo "creating object file \"$OUTPUT\" from files: $FILES with wx-config in mind"

g++ $FILES -o $OUTPUT $(wx-config --cxxflags --libs)

