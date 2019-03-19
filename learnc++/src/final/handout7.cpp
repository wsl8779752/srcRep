bool operator < (const class A& a1, const class A &a2){
    return a1.get_size() < a2.get_size();
}
template<class T>
struct MyLarge:public binary_function<T,T,bool>{
    bool operator()(const class A& a1, const class A &a2){
        const char *ca1 = new char[a1.get_size()];
        const char *ca2 = new char[a2.get_size()];
        ca1 = a1.get_name().c_str();
        ca2 = a2.get_name().c_str();
        return *ca1 < *ca2;
    }
};
template<class T,class Pred>
void Show(T first, T second, Pred opred){
    for(; first!= second ;++first)
        opred( first);
};
struct Print {
    public:
        Print(){}
        void operator()(list<A>::iterator it){
            cout << *it<<" ";
  }
};

