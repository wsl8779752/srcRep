class MyString:public string 
{ 
    public: 
        MyString(); 
        MyString(const MyString &s);
        MyString(const string &s);
        MyString(const char *s);
        MyString operator()(size_t i, size_t j);
        virtual ~MyString (); 
}; 
MyString::MyString():string(){}
MyString::MyString(const MyString &s):string(s){
}
MyString::MyString(const string &s):string(s){
}
MyString::MyString(const char *s):string(s){ 
} 
MyString MyString::operator() (size_t i, size_t j){ 
    return substr(i,j);
} 
MyString::~MyString(){
}
void qsort(MyString *a,int len,size_t kkk,int (*comparep)(const void*,const void *)){
    for(int i=0;i<3;i++)
        for( int j = 0;  j < len-i-1; j++) { 
            if( comparep( a+j,a+j+1 ) > 0 ){ 
                MyString temp = *(a+j);
                *(a+j) = *(a+j+1) ;
                *(a+j+1) = temp;
            } 
        }     
}
