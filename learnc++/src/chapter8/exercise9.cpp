#include<iostream>
#include<set>
#include<iterator>
using namespace std;
int main(){
	int a[]={8,7,8,9,6,2,1};
    multiset<int> v(a,a+7);
	for(int i=0;i<7;i++){
		;
	}
	ostream_iterator<int> o(cout,"");
	copy(v.begin(),v.end(),o);
	system("pause");
	return 0;
}
