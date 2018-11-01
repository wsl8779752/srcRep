class CType 
{ 
    public: 
        void setvalue(int n){ k = n;} 
        int operator++(int){ int ans = k ; k*=k; return ans;  }
        int k;
}; 
