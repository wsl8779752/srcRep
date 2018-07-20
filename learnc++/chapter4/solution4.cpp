#include <iostream> 
#include <sstream>
#include <cstdio> 
#include <cstring> 
#include <string> 
#include <algorithm>
#include <limits> 
using namespace std;
class dataDef 
{ 
    public: 
        dataDef (); 
        dataDef(char *s);
        dataDef(dataDef &n);
        virtual ~dataDef (); 
        void dataInit();
        char *data; 
        char *operator+(dataDef &temp);
        char *operator-(dataDef &temp);
        char *operator*(dataDef &temp);
        char *operator/(dataDef &temp);
        dataDef & operator=(char *str);
    private: 
        int len;
}; 
dataDef::dataDef(){
    data = NULL; 
    len = 0 ;
}
dataDef::dataDef(char *s){
    int length =(int) strlen(s);
    if(length == 0) {
        delete data;
        data  =  NULL ;
        len = 0 ;
    }
    data = new char[length+1];
    memcpy(data,s,(size_t)(length+1));
    len =  length ;
}
dataDef::dataDef(dataDef &n){
    if(n.len == 0)
    {
       delete data;
       data = NULL ;
       len = 0; 
       return ;
    }
    if(len != n.len){
        delete data;
        data  = new char [n.len+1];
    }
    memcpy(data,n.data,(size_t)(n.len+1));
}
dataDef::~dataDef(){
    delete data;
}
void dataDef::dataInit(){
    len  = strlen(data);
}
char *dataDef:: operator+(dataDef &temp){
    int maxlen = max(len,temp.len);
    char *ans = new char[maxlen+2];
    int i =0;
    char carry=0, add1,add2;
    ans[0] = '0';
    ans[maxlen+1] = '\0';
    while( len-i > 0 || temp.len-i > 0 || carry==1){
        add1 = len-i>0? data[len-1-i]:'0';
        add2 = temp.len -i >0? temp.data[temp.len-i-1]:'0';
        ans[maxlen-i] = carry + add1 +add2 -'0';
        if( ans[maxlen-i] > '9'){
            carry = 1;
            ans[maxlen-i] -= 10;   //"相当于字符‘１０’
        }
        else { 
            carry = 0 ; 
        } 
        i++; 
    }
    if(ans[0] == '0'){
        char *ans2 = new char[maxlen+1];
        memcpy(ans2,ans+1,(size_t) (maxlen+1));
        delete []ans;
        return ans2;
    }
    return ans;
}
char *dataDef::operator-(dataDef &temp){
    int signFlag,i=0;
    char borrow;
    dataDef *bigOne,*smallOne ;
    if( len > temp.len) {
        signFlag = 1; 
    }
    else if (len< temp.len) { 
        signFlag = -1 ; 
    } 
    else { 
       signFlag =  strcmp(data,temp.data);
    }

    if(signFlag == 0){
        char *ans = new char[2]; 
        ans[0] = '0';
        ans[1] = '\0';
        return ans;
    }
    else if (signFlag > 0) { 
       bigOne = this ;
      smallOne =  &temp ; 
    }
    else { 
        bigOne = &temp;
        smallOne = this ;
    }  
    int maxlen = bigOne->len; 
    char *ans = new char[maxlen+2]; 
    borrow = 0;
    while(bigOne->len-i>0 || borrow == 1)
    { 
        char a = bigOne->len-i > 0 ? bigOne->data[bigOne->len-i-1]:'0';
        char b = smallOne->len-i>0 ? smallOne->data[smallOne->len-i-1]:'0';
        ans[maxlen-1-i] = a - b + '0'-borrow;
        if( ans[maxlen-1-i]  < '0'){
            ans[maxlen-1-i] += 10;
         borrow = 1;   
        
        }
        else { 
            borrow = 0; 
        }       
        i++ ;
    }
    /**
     * @brief 从头开始遍历，删除前置０，并补充符号位
     */
    i = 0;    
    while(ans[i] == '0') i++;
    char *ans2 = new char[maxlen-i+2];
    if( signFlag < 0 ){
        ans2[0] = '-';
        memcpy(ans2+1,ans+i,(size_t)(maxlen-i));
        ans2[maxlen-i+1] = '\0'; 
    }
    else { 
        memcpy(ans2,ans+i,(size_t)(maxlen-i)); 
        ans2[maxlen-i] = '\0';
    } 
    delete []ans;
    return ans2 ;
}
char *dataDef::operator*(dataDef &temp){ 
    dataDef *bigOne= this,*smallOne=&temp ;
    int j,k;
    if (len< temp.len) { 
        bigOne = &temp;
        smallOne = this ;
    }
    int totalLen =  bigOne->len + smallOne->len ;
    char product,carry;
    char *bigoneDataToInt = new char[bigOne->len ];
    memcpy(bigoneDataToInt,bigOne->data,  sizeof(char)*((size_t)bigOne->len ));
    for ( int i = 0; i < bigOne->len ; ++i) { //将字符转换为数字，方便计算
        bigoneDataToInt[i]-='0'; 
    } 
    char *process = new char[bigOne->len+1 ];
    char *ans = new char[totalLen+1];
    memset(ans,'0',(size_t)totalLen);
    for ( int i = 0; i < smallOne->len ; ++i) { 
        carry = 0 ;
        memset(process,0,(size_t)(bigOne->len+1) );
        for (  j = 0; j < bigOne->len ; ++j) { 
             product = bigoneDataToInt[bigOne->len-1-j]*( smallOne->data[smallOne->len -1-i]-'0');   
             product += carry ;
             carry = product/10;
             product = product%10;
             process[bigOne->len-j] = product; 
        }             
        process[0] = carry ;
        //将ans加上process
        carry = 0 ; 
        j = bigOne->len ;
        while ( j >=0 || carry) { 
            k = smallOne->len - i + j - 1;
            ans[k]=ans[k]+ process[j] + carry;
            if( ans[k] > '9') {
                carry = 1 ;
                ans[k] -= 10;
            }
            else carry = 0 ;
            j-- ;
        }      
    } 
    ans[totalLen] = '\0';
    if (ans[0]== '0'){
        char *ans2 =  new char[totalLen];
        memcpy(ans2,ans+1,(size_t)totalLen);
        delete [] ans;
        return ans2;
    }
    delete [] bigoneDataToInt;
    delete [] process;
    return ans ;
} 
char *dataDef::operator/(dataDef &temp){
    int k= 1;
    if(len < temp.len || (len == temp.len && (k = strcmp(data,temp.data))<0 )) // data<temp.data
    {
        char *ans = new char[2];
        ans[0] = '0';
        ans[1] = '\0';
        return ans;
    }
    else if (len == temp.len && k == 0) { 
        char *ans = new char[2];
        ans[0] = '1';
        ans[1] = '\0'; 
        return ans ;
    }
   else { 
   }  
   char *ans = new char[len+1]; 
   unsigned  int i =0;
   char *p ;
   dataDef c(*this),e;
   stringstream ss;
   while( c.data[0]!='-')
   {
       p = c  - temp ;
       c = p;       
       i++ ;
       if (i== UINT_MAX) { 
       ss<<i;
       dataDef d((char *) ss.str().c_str());
       e = ans ;
       ans = e+d;  
     }     
   }    
   return ans; 
}
dataDef &dataDef::operator=(char *str){
    int strLength =(int) strlen(str);
    if( len!= strLength ){
        delete[] data;
        data = new char[strLength+1];
    }
    memcpy(data,str,(size_t)(strLength+1));
    len = strLength ;
    return *this;
}
int main(){
    char input_operator ,*c;
    string  first,second;
    cin>>first>>input_operator>>second;
    dataDef a((char *)first.c_str()),b((char *)second.c_str());
    switch (input_operator) { 
        case '+':  
        { 
          c = a + b;                 
        } ;
        break; 
        case  '-':{c = a -b ;};
        break;          
        case '*':{c =a*b;};
        break;
        case '/':{c =a/b}
        break;         
        default: { 
        } 
        break; 
    } 
    printf("%s",c);
    delete c;
}
