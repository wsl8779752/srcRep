#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;
class Student
{ 
    public: 
        int input();
        void calculate();
        void output();        
        Student(){
            average = 0;
        }
    private: 
        string name;
        string id;
        unsigned int age;
        unsigned int grade[4];
        unsigned int average;
}; 
int Student::input(){
    char comma;
    //cout<<"请输入学生信息，用逗号隔开:";
    getline(cin,name,',');
    cin>>age>>comma;
    getline(cin,id,',');
    cin>>grade[0]>>comma>>grade[1]>>comma>>grade[2]>>comma>>grade[3] ;
    return 0;
};
void Student::calculate()
{   
    for (unsigned int i = 0; i < 4; ++i) { 
        average += grade[i];
    } 
    average /= 4;
};
void Student::output()
{
    cout<<name<<','<<age<<','<<id<<','<<average<<endl;
};
int main() {
    Student student;        // 定义类的对象
    student.input();        // 输入数据
    student.calculate();    // 计算平均成绩
    student.output();       // 输出数据
    return 0;
}
