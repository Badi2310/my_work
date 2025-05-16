#!/bin/bash
FILE_PATH=$1
curl -L "http://mipt-master.atp-fivt.org:50070/webhdfs/v1{$FILE_PATH}?op=OPEN&length=10"
echo
