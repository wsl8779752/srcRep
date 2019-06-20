const char *letters[10] = { " ","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };


void add_answer( char *digits ,int rows , int len, int *pindex, char *temp, char **ans){
	char *act_s;
        if( rows < len ) {
            act_s = letters[ digits[rows] - '0'] ;
            while(  *act_s ){
                 temp[rows] = *act_s++;                 
                 add_answer( digits, rows+1,len,pindex,temp,ans) ;
            }
        }
         else{
            act_s = letters[ digits[rows] - '0'] ;
			while(  *act_s ){
                temp[rows] = *act_s++;
            	ans[*pindex] = malloc(sizeof(char)*(len+1));
                strcpy (ans[*pindex],temp);
                (*pindex)++;
            }
           return  ;
         }
}

char** letterCombinations(char* digits, int* returnSize) {
    int i, j , len, pindex;
    if( digits == NULL || ( len = strlen( digits ) ) == 0 ) return NULL;
    for ( *returnSize = 1, i  = 0 ; i< len ; i ++ ){
        if ( ( j = digits[i] - '0') < 2  || j > 9 ) return NULL;
       	*returnSize = (*returnSize) * strlen(letters[j]);
    }
    char *temp = malloc( sizeof(char)* (len+1)) ;
    char **ans  = malloc( sizeof(char *) * (*returnSize)) ;
    temp[len] = '\0';
    pindex  = 0 ;
    add_answer ( digits, 0,len-1,&pindex,temp,ans) ;
    return ans ;
}
