#!/usr/bin/env python

import sys
import random

my_id_list = []
current_line = ""
current_words_count = 0
rand_limit = random.randint(1, 5)
for line in sys.stdin:
    try:
        _, id = line.strip().split('\t', 1)
    except ValueError as e:
        continue
    if current_words_count < rand_limit:
        my_id_list.append(id)
        # current_line += (" " + id)
        current_words_count += 1
    else:
        rand_limit = random.randint(1, 5)
        # print(current_line.strip())
        print(",".join(my_id_list))
        # current_line = id
        my_id_list = [id]
        current_words_count = 1

if current_words_count != 0:
    # print(current_line)
    print(",".join(my_id_list))
