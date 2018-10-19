#include <iostream>
#include <string>
#include <vector>
using namespace std;
template<class T>
class MyClass 
{ 
    public: 
        MyClass (T *begin,int n):array(n){
            copy(begin,begin+n,array.begin());
        } 
        void list(){
        	typename std::vector<T>::const_iterator i; 
            for(i = array.begin();i!= array.end();++i){
                cout<<*i<<",";
            }
        }
         
    private: 
        vector<T>	array; 
}; 
int main()
{
   string array[4] = {"tt","x","mary","John"} ;
   MyClass<string>  obj(array,4);
   obj.list();
   return 0;
}
