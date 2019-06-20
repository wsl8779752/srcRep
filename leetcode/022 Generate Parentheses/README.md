###### 22. Generate Parentheses
```
程序逻辑全对，唯一错误的地方在realloc　ans这里，没有充分考虑到在递归调用的时候，ans变成了局部变量，
重新分配的ａｎｓ不会影响全局，导致程序返回错误的值。其他都对。这里可以优化下？？
算法：
递归调用放置括号，每次递归中在一个位置上先放左括号，再放右括号，直到末位置结束。在过程中用stackSize 这个数来计算放置的左括号数（相当于堆栈数）。递归中要始终使得右括号数不大于左括号数。
在递归函数中判断：
1. 如果已经放置的左括号数小于剩余位置数，则放置左括号。并递归下一层( stackSize+1 ,from+1 ,to)
2. 如果已经放置的左括号StackSize > 0 ,则放置右括号。
	１.　如果放置右括号后，达到末尾位置，则复制数据到返回值，然后返回
    ２．如果放置括号后，没达到末尾位置，则递归下一层(stackSize-1,from+1,to)

伪代码：                                                            
  1  void addParenthesis(int stackSize, int from ,int to ,int *returnSize,char **ans, char * temp)
  2      if( stackSize < to - from ) :          
  3          temp[from] = '(';                  
  4          addParenthesis(stackSize+1 ,from+1,to,returnSize,ans,temp);
  5      if(stackSize > 0 ) :        temp[from] = ')';       
  6          if( from == to) :                  
  7              ans = realloc(ans, (*returnSize+1)*sizeof(char *));
  8              ans[*returnSize] = malloc( sizeof(char) * (to+2)) ;
  9              strcpy(ans[*returnSize],temp );*returnSize += 1;         
 10          else :addParenthesis(stackSize -1 ,from+1,to,returnSize,ans,temp);
 11      return ;                    
 12                 
 13  char** generateParenthesis(int n, int* returnSize) 
 14      char *temp =  malloc( sizeof(char)*(2*n+1));   
 15      char **ans =  malloc( sizeof(char *));         
 16      temp[2*n] = '\0';           
 17      *returnSize = 0;                       
 18      addParenthesis(0,0,2*n-1,returnSize,ans,temp); 
 19      free (temp);                
 20      return ans ;                                       
程序逻辑全对，唯一错误的地方在realloc　ans这里，没有充分考虑到在递归调用的时候，ans变成了局部变量，
重新分配的ａｎｓ不会影响全局，导致程序返回错误的值。其他都对。

修正reaaloc ans问题代码。
1 int addParenthesis(int stackSize, int from ,int to ,int *returnSize,char ***ans ,char * temp):                           
2     if( stackSize < to - from ):
3         temp[from] = '(';
4         addParenthesis(stackSize+1 ,from+1,to,returnSize,ans,temp);
5     if( stackSize > 0 ) :
6         temp[from] = ')';
7         if( from == to):
8             *ans = realloc( *ans, (*returnSize+1) * sizeof(char *));
9             (*ans)[*returnSize] = malloc( sizeof(char) * (to+2)) ;
10             strcpy( (*ans)[*returnSize],temp ); *returnSize += 1;
11         else addParenthesis(stackSize -1 ,from+1,to,returnSize,ans,temp);
12      return 0;
13  
14 char** generateParenthesis(int n, int* returnSize) :
15     char *temp =  malloc( sizeof(char)*(2*n+1));
16     char **ans = (char **) malloc( sizeof(char *));
17     temp[2*n] = '\0';
18     *returnSize = 0;
19     addParenthesis(0,0,2*n-1,returnSize,&ans,temp);
20     free (temp);
21     return ans ;
Tips:
1. (*ans)[*returnSize] = malloc( sizeof(char) * (to+2))　这里是to+2，因为 to =  2n-1;
2. realloc ans是局部变量，realloc了不影响全局，所以必须用*ans来影响全局。       
```
