#!/usr/bin/python
# FileName: try_except.py

import sys

try:
    s = raw_input ( ' Enter something-->')
except EOFError:
    print '\n why did you do an EOF on me?'
except:
    print '\nsome thing error happen.'

print 'Done'
