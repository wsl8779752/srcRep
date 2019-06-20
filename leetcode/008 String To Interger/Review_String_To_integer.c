int myAtoi(char* str) {
    bool sign ;
    int i ,len ,ans,old_ans,ones_place;
    len = strlen(str);    
    for( i = 0;i<len && str[i]==' ';i++ ) ; //jump over all leading whitspace
    if (i == len) return 0;
    
    /* deal with first non-whitespace character*/
    sign = false;   
    if(str[i] == '+') { 
        sign = false;
        i++ ;
    }    
    else if( str[i] == '-') 
    {    
        sign = true;
        i++ ;
    }
    for (ans = 0; i < len && str[i]>='0' && str[i]<='9'; i++ ){  //calculate ans untill reach a non_number character or end of string.
        old_ans = ans;
        ones_place = str[i]-'0';  //计算个位
        ans*= 10;
        ans += ones_place ;
        if( old_ans != ans/10 )
            return sign ? INT_MIN : INT_MAX ;
    }         	
    return sign ? -ans:ans;    
}
