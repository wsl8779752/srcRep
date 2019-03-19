#include <iostream>
#include <cmath>
#include <vector> 
#include <set> 
using namespace std;


//判断一个数是否为质数
bool isPrime(unsigned int iVal)
{
    for (unsigned int i = 2; i <= sqrt((float)iVal); i++)
    {
        if (iVal % i == 0)
            return false;
    }
    return true;
}

//得到一个数的质因数数目
unsigned int getPrimeFactor(unsigned int a)
{
    unsigned int sum = 0;
    unsigned int k = 0;
    for (unsigned int i = 2; i <= sqrt((float)a); i++)
    {
        if (a % i == 0)//即a/i = k，无余数
        {
            k = a / i;
            if (i != k && isPrime(k))
                sum += 1;
            if (isPrime(i))
            {
                sum += 1;
            }
        }
    }
    return sum;
}

struct Myless{
    bool operator()(unsigned int a1, unsigned int a2){
        if( getPrimeFactor(a1) < getPrimeFactor(a2)) return true;
        else if( getPrimeFactor(a1) > getPrimeFactor(a2) ) return false;
        else return a1<a2;
    }
};
int main(){
    unsigned num;
    cin>>num;
    vector<unsigned int> element(10);
    multiset<unsigned int,Myless> ss;
    vector<unsigned int>::iterator iter;
    while(num--)
    {
        for( iter = element.begin(); iter != element.end(); ++iter) {
           cin>> *iter;  
        } 
        ss.insert(element.begin(),element.end());
        cout<< *(--ss.end())<<" "<<*ss.begin()<<endl;   
        ss.erase(ss.begin());
        ss.erase(--ss.end());
    }  
    return 0;
}
