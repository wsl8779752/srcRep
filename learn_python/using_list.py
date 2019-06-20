#!/usr/bin/python
# FileName: using_list.py

shoplist=['apple','banana','carrot']
print 'I have',
for item in shoplist:
    print item ,
print '\nI also have to buy rice.'
shoplist.append('rice')
print '\nafter add rice  in shoplist,My shopping list is now', shoplist
print '\nthe first item i will buy is', shoplist[0]
olditem = shoplist[0]
del shoplist[0]
print '\nI bought ',olditem
print '\nMy shoplist is now',shoplist
