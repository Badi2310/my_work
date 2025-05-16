#!/bin/bash
hadoop fsck "$1" -blocks -files 2>/dev/null | grep "Total blocks" | awk '{print $4}'
