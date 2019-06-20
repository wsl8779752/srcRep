
#! /usr/bin/python
#Filename: func_key.py

def printMax(x, y):
    '''Prints the maximum of two numbers.

    number must be integers.'''
    x = int(x)
    y = int(y)
    if x>y:
      print x ,'is maximum'
    else:
      print y , 'is maximum'
printMax(3,5)
print printMax.__doc__
