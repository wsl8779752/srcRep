#!/usr/bin/python
# FILEname: function_global.py

def func():
	global x
	print 'x is',x
	x = 2;
	print 'function change x to :',x

x =50
func()
print 'value of x is now',x

