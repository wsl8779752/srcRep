#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
using namespace std;
int main()
{
    unsigned long id ,id2;
    int num,n;
    vector<list<int> > MyList(10000);
    string cmd;
    cin>>n;
    while(n--){
        cin>>cmd;
        if ( cmd == "new") { 
            cin>>id;
        } 
        else if ( cmd == "add") { 
            cin>>id>>num;
            MyList[id].push_back(num); 
        } 
        else if ( cmd == "merge") { 
            cin >>id>>id2;
            MyList[id].splice(MyList[id].end(),MyList[id2]);  
        } 
        else if ( cmd == "unique") { 
            cin>>id;
            MyList[id].sort();
            MyList[id].unique(); 
        } 
        else if ( cmd == "out") { 
            cin>>id;
            /*list<int> temp(MyList[id]);*/
            /*temp.sort();*/
            MyList[id].sort(); 
            for (list<int>::iterator iter = MyList[id] .begin(); iter != MyList[id].end(); ++iter) {
                cout<<*iter<<" ";
            } 
            /*ostream_iterator<int> o(cout," ");*/
            //copy(MyList[id].begin(),MyList[id].end(),o);
            cout<<endl;
        } 
    }
    //cout<<flush;
    return 0;
}
