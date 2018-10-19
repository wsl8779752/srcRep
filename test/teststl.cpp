#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main () 
{
	int myints[] = {10, 20, 30, 40, 50, 60, 70};
	vector<int> myvector;
	vector<int>::iterator it;
	
	myvector.resize(7);   // 为容器myvector分配空间
	
	//copy用法一：
	//将数组myints中的七个元素复制到myvector容器中
	copy ( myints, myints+7, myvector.begin() );
	
	cout << "myvector contains: ";
	for ( it = myvector.begin();  it != myvector.end();  ++it )
	{
		cout << " " << *it;
	}
	cout << endl;

	//copy用法二:
	//将数组myints中的元素向左移动一位
	copy(myints + 1, myints + 7, myints);

	cout << "myints contains: ";
	for ( size_t i = 0; i < 7; ++i )
	{
		cout << " " << myints[i];
	}
	cout << endl;

	return 0;
}
