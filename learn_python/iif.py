#!/usr/bin/python
# FIlename: iif.py
number = 23
guess = int( raw_input('Enter an integer: '))

if guess == number :
  print 'Congratulations,you guessed it.'
  print "(but you do not win any prizes!)"
elif guess < number:
  print 'No, it is a litthle higher than that '
#you can do whatever you want in a block ...
else:
  print 'No,it is a little lower than that'
  # you must have guess >number to reach here

print 'DOne'
#this last statement is always executed,after the if statement is executed:

