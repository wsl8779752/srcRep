#include <string>
#include <iostream>
using namespace std;

class Examinfo{
public:
    Examinfo(string name1, char grade):name(name1),mode(GRADE),grade(grade){}
    Examinfo(string name, bool pass):name(name),mode(PASS),pass(pass){}
    Examinfo(string name, int percent):name(name),mode(PERCENTAGE),percent(percent){}
    void show();


private:
    string name;
    enum{
        GRADE,
        PASS,
        PERCENTAGE
    }mode;
    union{
        char grade;
        bool pass;
        int percent;
    };
};

void Examinfo::show(){
    cout<<name<<":";
    switch (mode) {
        case  GRADE:
          cout<<grade;
          break;
        case  PASS:
          cout<<(pass?"PASS":"FAIL");
          break;
        case  PERCENTAGE:
          cout<<percent;
          break;
    }
    cout <<endl;
}
int main(){
    Examinfo course1("English",'B');
    Examinfo course2("Calculus",true);
    Examinfo course3("C++Progaming",85);
    course1.show();
    course2.show();
    course3.show();
    return 0;
}
