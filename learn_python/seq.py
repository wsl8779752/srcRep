#!/usr/bin/python
# FileName: seq.py

shoplist = ['apple','mango','carrot','bnana']

#Index or 'Subscription' operation
for i in range(-3,3):
    print "Item %d is %s" %( i, shoplist[i])

#Slicing on a list
print 'Item 1 to 3 is ',shoplist[1:3]
print 'Item 2 to end is',shoplist[2:]
print 'Item 1 to -1 is ',shoplist[1:-1]
print 'Item start to end is',shoplist[:]

#Slicing on a string
name = 'Weishulin'
print 'charachter 1 to 3 is ' ,name[1:3]
print 'character 2 to end is ',name[2:]
print 'character 1 to -1 is ',name[1:-1]
print 'characters starts to end is ',name[:]

