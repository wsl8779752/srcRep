#!/usr/bin/python
#Filename: break.py

running = True 
while running==True :
	s = raw_input('Enter someting:');
	if s== 'quit':
		break ;
	print 'the Length of input string is',len(s);
else:
	print 'while loop breaked'
print 'Done'

