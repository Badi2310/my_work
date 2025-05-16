#!/bin/bash
BLOCK_ID=$1
NODE="$(hdfs fsck -blockId "$BLOCK_ID" 2>/dev/null | awk '/Block replica/ {print $5; exit}' | sed 's#/default##')"
FULL_PATH="$(sudo -u hdfsuser ssh hdfsuser@$NODE "find / -name $BLOCK_ID -print -quit 2>/dev/null")"
echo "$NODE:$FULL_PATH"
