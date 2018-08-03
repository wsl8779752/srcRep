class Array2 
{ 
    public: 
        Array2();
        Array2 (int row1,int column1); 
        virtual ~Array2 (); 
        int * operator[](int j);         
        int& operator()(int i,int j);
        Array2 & operator=(Array2 &kk);
    private: 
        int **p;
        int row;
        int column;
}; 
Array2::Array2(){
   p = NULL; 
}
Array2::Array2(int row1, int column1):row(row1),column(column1){
    p = new int*[row];
    for ( int i = 0; i < row; ++i) { 
        p[i] = new int[column]; 
    } 
}
Array2::~Array2(){
    if(p){
        for ( int i = 0; i < row; ++i) { 
            delete p[i];
        } 
        delete p;
    }
}
int * Array2::operator  []( int i){
    return  p[i];
}
int &Array2::operator()(int i, int j){
    return p[i][j];
}
Array2& Array2::operator=(Array2 &kk){
    if( this == &kk) return *this;
    if( p ){
        for ( int i = 0; i < column; ++i)  delete p[i];
        delete p ;
        p = NULL ;
    }
    if( kk.p == NULL ) return *this;    
    row = kk.row;
    column = kk.column;
    p = new int*[row];
    for(int i = 0;i<row;++i){
        p[i] = new int[column];
        memcpy(p[i],kk.p[i],sizeof(int)*column);
    }
    return *this ;
}
