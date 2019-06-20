#!/usr/bin/python
#FileName: using_file.py

content = '''\
Progarmming is fun
when the work is done
if you wanna make your work also fun:
    use python!
'''

f = file('poem.txt','w')
f.write(content)
f.close()

f = file('poem.txt')
while True:
    line  = f.readline()
    if len(line) == 0:
        break
    print line,

f.close()
