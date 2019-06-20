bool isValid(char* s) {
    int i = 0,j;
    while( *s= '\0' ){
        while( s[i] == '{' || s[i] == '{' || s[i] == '('  ) i++;
        if( i ){
            for(j=0;j<i;j++){
                switch (s[i+j]){
                    case '}': if( s[i-j-1] !=  '{' ) return false; break;
                    case ')': if( s[i-j-1] !=  '(' ) return false; break;
                    case ']': if( s[i-j-1] !=  ']' ) return false; break;
                    default : return false;
                }
            }
        }
        else
            return false ;	
        s+=2*i;		
        i = 0;

    }
    return true;
}
