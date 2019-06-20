#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <string.h>
#define max(x,y)  ( x>y?x:y )

int lengthOfLongestSubstring(char* s) {

    int i,j,n,ans=0;
    n = strlen(s) ;
    int *hashmap =calloc(-1,sizeof(int)*128);

    for( i=0,j=0;j<n;j++){
        if( hashmap[s[j]]!=-1 )
        {
            i = max(i, (hashmap[s[j]]+1)) ;
        }
        ans = max(ans,j-i+1)  ;
        hashmap[s[j]] = j ;
    }
    return ans ;
}

int main()
{
    printf("%d",lengthOfLongestSubstring("c") );
    return 0;
}
