template <class T>
class CArray3D 
{ 
    public: 
        CArray3D (int i,int j,int k):s1(i),s2(j),s3(k){ 
            p = new T**[i];
			for (int i = 0; i < s1; i++)
			{
				p[i] = new T*[j];
				for (int j = 0; j < s2; j++)
				{
					p[i][j] = new T[k];
				}
			}
        }
        virtual ~CArray3D (){ 
			for (int i = 0; i < s1; i++)
			{
				for (int j = 0; j < s2; j++)
				{
                    delete p[i][j];
				}
                delete p[i];
			}
            delete p;
        }  
        T ***p;
        T **operator[](int i){ return p[i] ;}
    private: 
       int s1,s2,s3; 
};
