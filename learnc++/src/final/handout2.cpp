 Number(Number &n){ num = n.num; }
    int& value(){ return num;}
    Number& operator+(Number &n){
        num+=n.num;
        return *this;
    }
