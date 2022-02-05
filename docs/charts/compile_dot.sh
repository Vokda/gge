#!/bin/sh

if [ $# -lt 1 ]
then
	echo "no input file"
	exit 0
fi

in_file=$1
out_file=$(basename -s.dot ${in_file})
dot -Tpng $in_file -o $out_file.png
