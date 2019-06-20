#!/usr/bin/python
# FileName : finally.py

import time

try:
    f1 = file('poem.txt')
    while True:
        line = f1.readline()
        if len(line) ==0 :
            break
        time.sleep(2)
        print line,

finally:
    f1.close()
    print 'Cleaning up...closed the open file'

