#!/bin/bash

SIZE=$1
dd if=/dev/zero of=some_file bs="$SIZE" count=1 2> /dev/null
hdfs dfs -put some_file some_file > /dev/null
hdfs dfs -setrep -w 1 some_file > /dev/null
REAL_SIZE=$(hdfs dfs -du some_file | awk '{print $1}')
hdfs dfs -rm -skipTrash some_file > /dev/null
rm some_file
echo $(($REAL_SIZE - $1))

