char* convert(char* s, int numRows) {
    int i,j,len,interval,jump,index;
    len =  strlen(s) ;
    if (numRows == 1 || len == 0 ) return s;    
    char *ans =  malloc(sizeof(char)*(len+1)); //+1 for '\0'
    interval =  2*(numRows-1) ;    
    for (i = 0 ,index = 0; i < numRows; i++){
        for (j = i,jump = 2*i; j < len ; j += jump){  // j =len for '\0'in stirng end
            ans[index] = s[j];
            jump = interval -jump;
            if(jump) index++;
        }
    }
    ans[len] = '\0';
    return ans ;
}
