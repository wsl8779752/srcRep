#!/usr/bin/python
# FIlename: iif.py
number = 23
running = True 
while running :
	guess = int( raw_input('Enter an integer: '))
	if guess == number :
		running =False
		print 'Congratulations,you guessed it.'
		print "(but you do not win any prizes!)"
	elif guess < number:
		print 'No, it is a little low  than that '
		 #you can do whatever you want in a block ...
	else:
		print 'No,it is a little high than that'
		  # you must have guess >number to reach here
else:
	print 'while loop breaked for the right number'
print 'Done'
#this last statement is always executed,after the if statement is executed:

