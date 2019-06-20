#!/usr/bin/python
# FileName: rasing.py

class ShortInputException(Exception):
    ''' A user defined exception class.'''
    def __init__(self,length,leastlength):
        Exception.__init__(self)
        self.length = length
        self.leastlength = leastlength

try:
    s= raw_input('please enter something-->')

    if len(s)<3:
        raise ShortInputException(len(s),3)
except EOFError:
    print 'Why you input EOF'
except ShortInputException, x:
    print 'ShortInputException: the input was of length %d,\
expecting at leaste %d' %(x.length,x.leastlength)

else:
    print 'No exception was raised'



    
