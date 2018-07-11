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
        char name[20];
        unsigned int age;
        unsigned int stuNumber;
        unsigned int grade[4];
        unsigned int average;
};
int Student::input(){
    cout<<"请输入学生信息，用逗号隔开:";
    string str;
    cin.getline(name,20,',');
    scanf("%u,%u,%u,%u,%u,%u",&age,&stuNumber,grade,grade+1,grade+2,grade+3);
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
    cout<<name<<','<<age<<','<<stuNumber<<','<<average<<endl;
};
int main() {
    Student student;        // 定义类的对象
    student.input();        // 输入数据
    student.calculate();    // 计算平均成绩
    student.output();       // 输出数据
    return 0;
}
