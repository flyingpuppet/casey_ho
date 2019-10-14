#!/bin/bash

#  This script use to get the total size of the specified sections.

S_SIZE=0
LINE=""

if [ $# -le 3 ]; then
	echo "too few arguments."
	exit 1
fi

IN_FILE=$1
OUT_FILE=$2
EXT_NUM=$3

if [ ! -f $IN_FILE ]; then
	echo "$IN_FILE: does not exist."
	exit 1
fi

shift
shift
shift

while [ $# -gt 0 ] 
do
	LINE=`grep -n " $1" $IN_FILE | sed 's/:.*$//'`
	LINE=$(( $LINE + 1 ))
	SIZE=`sed -n "$LINE p" $IN_FILE | sed 's/(.*$//' | sed 's/^.*=//'`
	S_SIZE=$(( $S_SIZE + $SIZE ))
	shift
done

S_SIZE=$(( $S_SIZE + $EXT_NUM ))

S_SIZE=$(awk 'BEGIN{printf("%#x",'$S_SIZE')}')

echo $S_SIZE > $OUT_FILE
exit 0
