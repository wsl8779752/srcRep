int addParenthesis(int stackSize, int from ,int to ,int *returnSize,char ***ans ,char * temp){
    if( stackSize < to - from ){
        temp[from] = '(';
        addParenthesis(stackSize+1 ,from+1,to,returnSize,ans,temp);
    }
    if( stackSize > 0 ) {
        temp[from] = ')';
        if( from == to){
            *ans = realloc( *ans, (*returnSize+1) * sizeof(char *));
            (*ans)[*returnSize] = malloc( sizeof(char) * (to+2)) ;
            strcpy( (*ans)[*returnSize],temp );
            *returnSize += 1;
          //  return 0 ;
        }
        else addParenthesis(stackSize -1 ,from+1,to,returnSize,ans,temp);

    }
     return 0;
}
char** generateParenthesis(int n, int* returnSize) {
    char *temp =  malloc( sizeof(char)*(2*n+1));
    char **ans = (char **) malloc( sizeof(char *));
    temp[2*n] = '\0';
    *returnSize = 0;
    addParenthesis(0,0,2*n-1,returnSize,&ans,temp);
    free (temp);
    return ans ;
}
