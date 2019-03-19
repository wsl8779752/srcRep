class A 
{ 
    public: 
        A(int n){ 
            name ='A';
            age = n;
        }
        bool operator<( A& n){
            return  age < n.age;
        }
        char name;
        int age;
        friend ostream &operator<<(ostream &n, A *b){
            n<<(b->name)<<" "<<(b->age)<<endl;
            return n;  
        }
}; 
class B :public A 
{ 
    public: 
        B(int n):A(n){name = 'B';} 
}; 

struct Comp{
    bool operator()(const A* a1, const A* a2){
        return (*a1).age < (*a2).age;
    }
};
void Print( A* it){
    cout<<it;
}
