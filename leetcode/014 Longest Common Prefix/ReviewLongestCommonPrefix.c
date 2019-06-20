char* longestCommonPrefix(char** strs, int strsSize) 
{
    int i,j,len0 ,temp ;
    if ( strsSize == 0 ) return  "" ;
    len0 =  strlen ( strs[0] ) ;
    char *ans  =  malloc ( sizeof(char) * (len0+1));
    strcpy( ans , strs[0] );
    for( i = 1; i< strsSize ; i++ ){
        temp = 0 ;
        for( j = 0;j < len0; j++){
            if( ans[j] ==  strs[i][j]) temp++;
            else{
                ans[j] = '\0';
                break ;
            }
        }
        if (temp == 0 ) return "";
        if (temp < len0) len0 = temp ;
    }
    return ans ; 
}       
