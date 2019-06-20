#!/usr/bin/python
#FileName: using_dict.py

ab = { 
        'Weishulin': 'rensheng946@163.com',
        'Yangle':'413045384@qq.com',
        'Spammer':'Spammer@hotmail.com'
     }
print "Weishulin's address is%s" % ab['Weishulin']

#adding a value
ab['Lilei']='Lilei@163.com'

#Deleting a key/value pair
del ab['Spammer']

print "there are %d items in ab" % len(ab)

for name, addr in ab.items():
    print "%s's address is %s" % (name, addr)

if 'Yangle' in ab:
    print "yangle's address is %s" % ab['Yangle']


