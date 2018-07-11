#include <iostream>

using namespace std;
class Sample {
    public:
        int v;
        Sample(const Sample &x){
            if(x.v == 5| x.v == 9)
                v = 9;
            else
               v = 22; 
        }
        Sample(int value){
            v = value;
        }
        Sample(){}
};
void PrintAndDouble(Sample o)
{
    cout << o.v;
    cout << endl;
}
int main()
{
    Sample a(5);
    Sample b = a;
    PrintAndDouble(b);
    Sample c = 20;
    PrintAndDouble(c);
    Sample d;
    d = a;
    cout << d.v<<endl;
    return 0;
}
