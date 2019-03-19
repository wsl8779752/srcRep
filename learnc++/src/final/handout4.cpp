class CType 
{ 
    public: 
        void setvalue(int n){ k = n;} 
        int operator++(int){ int ans = k ; k*=k; return ans;  }
        int k;
}; 
ostream&  operator<<(ostream &o,CType& n){ 
    o<<n.k;
    return o;
}

