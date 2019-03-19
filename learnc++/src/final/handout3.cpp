long sum(int *p,int n,int (*funcp)(int k)){
   long ans = 0;
   for ( int i = 0; i < n; ++i) { 
        ans += funcp(p[i]); 
   }  
   return ans;

}
