#!/usr/bin/env bash

OUT_DIR="out"
NUM_REDUCERS=8

hadoop fs -rm -r -skipTrash ${OUT_DIR}

yarn jar /opt/cloudera/parcels/CDH/lib/hadoop-mapreduce/hadoop-streaming.jar \
    -D mapred.job.name="my_110_example" \
    -D mapreduce.job.reduces=${NUM_REDUCERS} \
    -files mapper.py,reducer.py \
    -mapper ./mapper.py \
    -reducer ./reducer.py \
    -input /data/ids \
    -output $OUT_DIR

hdfs dfs -cat ${OUT_DIR}/part-* | head -n 50

