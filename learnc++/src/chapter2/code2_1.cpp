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
    private: 
        char name[20];
        unsigned int age;
        unsigned int stuNumber;
        unsigned int grade[4];
        unsigned int average=0;
}; 
int Student::input(){
    cout<<"请输入学生信息，用逗号隔开:";
    string str;
    cin.getline(name,20,',');
   /* uint32_t *p = &age;*/
    //uint8_t n = sizeof(uint);
    //for (uint8_t i = 0; i < 4; ++i) { 
        //cin.getline(*p , 20 ,',');
        //p += n ; 
    /*}*/            
    scanf("%u,%u,%u,%u,%u,%u",&age,&stuNumber,grade,grade+1,grade+2,grade+3);
    //cin>>age>>stuNumber>>grade[0]>>grade[1]>>grade[2]>>grade[3];
    //cout<<"student.stuNumber:"<<age<<stuNumber<<endl;
    return 0;
};
void Student::calculate()
{   
    for (auto& e : grade){
        average+= e;
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
