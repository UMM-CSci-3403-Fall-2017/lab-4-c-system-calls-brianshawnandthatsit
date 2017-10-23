#!/bin/bash
#take input and save a directory
dir=$1
#go to the path
cd $dir
#get the number of regular files
num_regular=$(find . -type f | wc -l)
#get the numeber of directories
num_dirs=$(find . -type d | wc -l)
#print out the result
echo "There were $num_dirs directories."
echo "There were $num_regular regular files."
