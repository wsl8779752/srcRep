template <class T >
class CMyistream_iterator 
{ 
    private:
        T value ;
        istream &iskk;
    public: 
        CMyistream_iterator(istream &tempa):iskk(tempa){ 
           iskk>>value;
        } 
        T operator*(){return value;}
        void operator++(int){iskk>>value; }
        virtual ~CMyistream_iterator (){} 
}; 
