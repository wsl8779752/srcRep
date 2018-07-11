#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;
class headQuators 
{ 
    public: 
        headQuators(string name1){ name = name1;}; 
        virtual ~headQuators (); 
        void setLifeElement(int n){
             life_element = n ;
        } 
        void setManufacot_sequency:(){};
        int manufactor_warrior(string warrior_name);
    private: 
        static int life_element; 
        string manufactor_sequence[5];
        string name;
}; 
class warrior 
{ 
    public: 
        warrior (); 
        virtual ~warrior (); 
         
    private: 
        int hp;
        int number;
        int damage;
}; 
int main(){
    headQuators RedCommand("red"), Blue("blue");
        



}
