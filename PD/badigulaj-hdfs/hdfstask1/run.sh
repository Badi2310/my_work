#!/bin/bash

block_zero=$(hdfs fsck /data/twitter/twitter.txt -files -blocks -locations | grep -E '^0\. BP-')
ips=($(echo "$block_zero" | grep -oP 'DatanodeInfoWithStorage\[\K[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}'))

node=$(cat /etc/hosts | grep ${ips[0]} | awk '{print $2}')
echo "$node"


