#include <iostream>
using namespace std;
int main ()
{
    int my_array[5] = {1, 2, 3, 4, 5};
    // 每个数组元素乘于 2
    for (int &x : my_array)
    {
        x *= 2;
        cout << x << endl;  
    }
}
