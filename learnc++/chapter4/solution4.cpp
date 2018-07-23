#include <iostream>
#include <sstream>
#include <cstdio> 
#include <cstring> 
#include <string> 
#include <algorithm>
#include <climits> 
using namespace std;
class dataDef 
{ 
    public: 
        dataDef (); 
        dataDef(const char *s);
        dataDef(dataDef &n);
        virtual ~dataDef (); 
        void dataInit();
        char *data; 
        dataDef operator+(dataDef &temp);
        dataDef operator-(dataDef &temp);
        dataDef operator*(dataDef &temp);
        dataDef operator/(dataDef &temp);
        dataDef & operator=(const char *str);
        dataDef & operator=(const dataDef &temp);
        void out();
    private: 
        int len;
}; 
dataDef::dataDef(){
    data = NULL; 
    len = 0 ;
}
dataDef::dataDef(const char *s){
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
       data = NULL ;
       len = 0; 
    }
    else { 
        data  = new char [n.len+1];
        len = n.len ;
        memcpy(data,n.data,(size_t)(n.len+1));
    } 
}

dataDef::~dataDef(){
    delete data;
}
void dataDef::dataInit(){
    len  = (int) strlen(data);
}
dataDef dataDef:: operator+(dataDef &temp){
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
        ans = ans2;
    }
    dataDef n1(ans);
    delete [] ans;
    return n1;
}
dataDef dataDef::operator-(dataDef &temp){
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
        dataDef n1(ans);
        delete []ans;
        return n1;
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
        ans[maxlen-i] = a - b + '0' - borrow;   //从ans[maxlen-1]开始计算答案
        if( ans[maxlen-i]  < '0'){
            ans[maxlen-i] += 10;
            borrow = 1;   
        
        }
        else { 
            borrow = 0; 
        }       
        i++ ;
    }
    /**
     * @brief 遍历删除ans中的前置0
     * 从i =1 开始遍历是因为a-b 所得的数的位数不会超过a(a>b),假设ａ的长度是ｌ,而申请的ans的长度是(l+2);
     * 加上需要在ans末尾补充的'\0',用到的长度是l+1, 实际上ans[0]是用不到的，所以从ans[1]开始遍历
     */
    i = 1;    
    while(ans[i] == '0') i++;
    if( signFlag < 0 )
        ans[--i] = '-';
    ans[maxlen+1] = '\0';
    dataDef n1(ans+i);
    delete []ans;
    return n1 ;
}
dataDef dataDef::operator*(dataDef &temp){ 
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
    dataDef n1;
    if (ans[0]== '0'){
         n1 = ans+1;
    }
    else n1 = ans ;
    delete [] ans;
    delete [] bigoneDataToInt;
    delete [] process;
    return n1 ;
} 
dataDef dataDef::operator/(dataDef &temp){
    int k= 1;
    if(len < temp.len || (len == temp.len && (k = strcmp(data,temp.data))<0 )) // data<temp.data
    {
        char *ans = new char[2];
        ans[0] = '0';
        ans[1] = '\0';
        dataDef n1(ans);
        delete []ans;
        return n1;
    }
    else if (len == temp.len && k == 0) { 
        char *ans = new char[2];
        ans[0] = '1';
        ans[1] = '\0'; 
        dataDef n1(ans);
        delete []ans;
        return n1;
    }
   else { 
       unsigned  int i ,j = (unsigned int)(len - temp.len +2);
       char *ans = new char[j];
       dataDef c[9];
       for (c[1] = temp, i = 2; i<10; ++i) { 
            c[i] = c[i-1] +temp ;
       }
       dataDef dividend(*this); //被除数
       j = j-1;
       i = 0;
        while(j--){
            int t = strcmp(dividend.data,c[1].data) ;
            if(t < 0) {
                ans[i] = '0';
                for(int k= 9;k>0;k--){
                    
                }            
            }
            
            i++ ;
        }

   }   

}
dataDef &dataDef::operator=(const char *str){
    int strLength =(int) strlen(str);
    if( len!= strLength ){
        delete[] data;
        data = new char[strLength+1];
    }
    memcpy(data,str,(size_t)(strLength+1));
    len = strLength ;
    return *this;
}
dataDef & dataDef::operator=(const dataDef &n){ 

    if (data == n.data) return *this ;
    if(n.len == 0)
    {
       delete data;
       data = NULL ;
       len = 0; 
       return *this;
    }
    if(len != n.len){
        delete data;
        data  = new char [n.len+1];
        len = n.len ;
    }
    memcpy(data,n.data,(size_t)(n.len+1));
    return *this;
} 
void dataDef::out(){
    printf("%s",data);
}

int main(){
    char input_operator; 
    string  first,second;
    cin>>first>>input_operator>>second;
    dataDef a(first.c_str()),b(second.c_str()),c;
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
        case '/':{c =a/b;}
        break;         
    } 
    c.out();
}
