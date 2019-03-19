class CMy_add 
{ 
    public: 
        CMy_add(int &n):k(n){} 
        void operator()(int n){ k+= 0x07&n;}
    private:
        int  &k;
};
