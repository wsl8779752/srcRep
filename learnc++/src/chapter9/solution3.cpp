#include <iostream> 
#include <set> 
using namespace std;
int main()
{
    typedef multiset<int> mm1;
    int n,value;
    string cmd;
    mm1 v,erasednum;
    cin>>n;
    while(n--){
        cin>>cmd>>value;
        if( cmd == "add"){
            v.insert(value);
            cout<<v.count(value);
        }
        else if( cmd =="del"){
            cout<<v.count(value);
            mm1::iterator i;
            while( (i=v.find(value))!= v.end()){
               v.erase(i); 
               erasednum.insert(value);
            } 
        }
        else {
            if(v.find(value)!= v.end()|| erasednum.find(value)!= erasednum.end() )  //
                cout<<1;
            else cout<<0;
            cout<<" "<<v.count(value);
        }
        cout<<endl;
    } 
    return 0;
}

