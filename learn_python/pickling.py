#!/usr/bin/python
# FileName: pickling.py

import cPickle as p

shoplistfile = 'myshoplist.data'

shoplist = ['apple','banana','carrot','mango']
f = file(shoplistfile,'w')
p.dump(shoplist,f)
f.close()

del shoplist

f1 = file(shoplistfile)
theshop = p.load(f1)

print theshop

        
