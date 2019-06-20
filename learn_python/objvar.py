#!/usr/bin/python
# FileName: objvar.py
class Person:
    ''' represents a Person '''
    population = 0 
    
    def __init__(self,name):
        '''Intializes the Person's data.'''
        self.name = name
        print '(Initializes %s. )' %self.name
        Person.population += 1

    def __del__(self):
        '''I  am dying '''
        print '%s says bye.' % self.name
        Person.population -= 1
        if Person.population == 0:
            print ' I am the last one.'
        else:
            print ' Thres are still %d people left.' % Person.population

    def sayHi(self):
        ''' Greeting by the person.

        Really, that's all it does.'''
        print 'Hi, My name is %s.' % self.name

    def howmany(self):
        '''Prints the currenta population.'''
        if Person.population == 1:
            print 'I am the only Person here.'
        else:
            print ' We have %d people here.' % Person.population

Swaroop  = Person('Swaroop')
Swaroop.sayHi()
Swaroop.howmany()

kalam = Person('Abdul Kalam')
kalam.sayHi()
kalam.howmany()

Swaroop.sayHi()
Swaroop.howmany()
