class Schoolmember:
    num_of_member=0
    ''' Represent a school stuff,like techer/student/schoolmaster'''
    def __init__(self,name,age):
        self.name = name 
        self.age = age
        #num_of_member += 1

    def tell(self):
        '''This is basic lei telling the basic information'''
        print  'Name:%s  Age:%s tell by basic category '%(self.name,self.age)

class Student(Schoolmember):
    '''Represent a stutend'''
    def __init__(self,name,age,score):
        Schoolmember.__init__(self,name,age)
        self.score =  score
        print "Initiazing stutent %s " % self.name


    def tell(self):
        Schoolmember.tell(self)
        print ' Score: %d---tell by herit student' % self.score

class Teacher(Schoolmember):
    '''Represent a teacher '''
    def __init__(self,name,age,salary):
        Schoolmember.__init__(self,name,age)
        self.salary = salary
        print 'Initiazing teacher "%s"' % self.name
    def tell(self):
        Schoolmember.tell(self)
        print 'Salary:" %s"--- talk by herit Teacher' %self.salary

t =  Teacher('Mrs.Shrividya',32,30000)
s =  Student ('Weishulin', 18 , 93)

print 

member = [t ,s]
for members in member:
    members.tell()

    
