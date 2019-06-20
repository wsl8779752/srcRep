#!/usr/bin/python
#FileName : backup_ver1.py

import os
import time

#1. the files and directories to be backupd are specified in a list
source =['/home/wei/learn_python','/home/wei/Music']

#2. the backup must be stored in a main backpu directory
target_dir = '/home/wei/learn_python/backup/'

today = target_dir+time.strftime('%Y%m%d')

now = time.strftime('%H%M%S')

if not os.path.exists(today):
    os.mkdir(today)
    print 'Successfully created directory',today

comment = raw_input('Enter a comment -->')
if len(comment) == 0:
    target = today+os.sep+now+'.zip'
else:
    target = today+os.sep+now+comment.replace(' ','_')+'.zip'


zip_command ="zip -qr '%s' %s" %(target ,' '.join(source))

if os.system(zip_command) ==0:
    print 'Successful backup to',target
else:
    print 'BACK UP FAILED'
