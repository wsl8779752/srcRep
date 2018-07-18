#include <iostream> 
#include <string> 
#include <algorithm>
using namespace std;
class dataDef 
{ 
    public: 
        dataDef (); 
        virtual ~dataDef (); 
        void dataInit();
        char *data; 
        char *operator+(dataDef &temp);
        char *operator-(dataDef &temp);
        char *operator*(dataDef &temp);
        char *operator/(dataDef &temp);
    private: 
        int len;
        
}; 
dataDef::dataDef(){
    data  = new char[101];
}
dataDef::~dataDef(){
    delete data;
}
void dataInit(){
    len  = strlen(data);
}
char *dataDef:: operator+(dataDef &temp){
    int maxlen = max(len,temp.len);
    char *ans = new char[maxlen+2];
    int i =0;
    char carry, add1,add2;
    ans[0] = '0';
    ans[maxlen+1] = '\0';
    while( len-i > 0 || temp.len-i > 0 || carry==1){
        add1 = len-i>0? data[len-1-i]:'0';
        add2 = temp.len -i >0? temp.data[temp.len-i-1]:'0';
        ans[maxlen-i] = carry + add1 +add2 -'0';
        if( ans[maxlen-i] > '9'){
            carry = 1;
            ans[maxlen-i] -= ('9'+1);   //"相当于字符‘１０’
        }
        else { 
            carry = 0 ; 
        } 
        i++; 
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
        if( ans[maxlen-1-i] ) < '0'{
            ans[maxlen-1-i] += 10;
         borrow = 1;   
        
        }
        else { 
            borrow = 0; 
        }       
        i++ ;
    }
    i = 0;    
    
    while(ans[i] == '0') i++;
    if( signFlag < 0 ){
        char ans2 =  
    }

        
    //重头遍历，插入符号位 
    
    return ans ;
}

int main(){
    dataDef a ,b ;
    char input_operator ;
    cin>>a.data>>input_operator>>b.data;
    a.dataInit();
    b.dataInit();
    /*if(len_a < len_b ){*/
        //char *temp = a ;
        //a = b;
        //b = temp ;
        //int temp_len = len_a ;
        //len_a = len_b ;
        //len_b = temp_len ;
    /*}*/
    switch (input_operator) { 
        case '+':   { 
           a + b;                 
        } ;
        break; 
        case  '-':{ a -b ;};
        break;          
        case '*':{a*b};
        break;
        case '/':{a/b}
        break;         
        default: { 
        } 
        break; 
    } 
}
