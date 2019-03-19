template<class Key, class Value,class Pred = greater<Key> >
class MyMultimap :public multimap<Key,Value,Pred>{
    public:
        void Set(Key s ,Value score){
            typedef typename multimap<Key,Value,Pred>::iterator it;
            pair<it,it> tt = this-> equal_range(s); 
            for(;tt.first!=tt.second;tt.first++){
                (tt.first)-> second = score; 
            } 
        }

};
template<class Key, class Value>
ostream & operator<<(ostream &n, pair<Key,Value>p) 
{   n<< "(" << p.first << "," << p.second << ")";
    return n;
};

