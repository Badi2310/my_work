#!/usr/bin/env python

import sys
import random

for line in sys.stdin:
    try:
        id = line.strip()
    except ValueError as e:
        continue

    key = random.random() * 1000
    
    print("%d\t%s" % (round(key), id))
