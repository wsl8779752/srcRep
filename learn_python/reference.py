#!/usr/bin/python
# FileNanme: reference.py

print 'Simple Assignment'
shoplist = ['apple','mango','banana','carrot']
mylist= shoplist

del mylist[0]
print 'shoplist is',shoplist
print 'mylist is',mylist

#figure out wheather varible has the sanme property as the list:
i=0
j=i
j =3
print 'i is ',i
print 'j is ',j

print 'Copy by making a full slice'
mylist =  shoplist[:]
del mylist[0]

print 'shoplist is',shoplist
print 'mylist is ',mylist
#notice that now the tow list are different
