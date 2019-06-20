```
算法：
思路很简单，就是循环检测对数括号，直到末尾。
1. i = 0 ;
2. while( ×s= '\0' )
3. 		while（ s[i] == '{' or '{' or '('  ) i++;
4. 		if( i )
5. 			for(j=0;j<i;j++)
6. 				switch (s[i+j])
7.    				case '}': if( s[i-j-1] !=  '{' ) return False; break;
8.   . 				case ')': if( s[i-j-1] !=  '(' ) return False; break;
9. 					case ']'; if( s[i-j-1] !=  ']' ) return False; break;
10. 				default : return False;
11. 	else return False ；	
12. 	i = 0;
13. 	s+=2*i;		
14. return true；
上面的算法看似奏效，但实际上遇到 "(([]){})" 的字符串时，循环根本无法处理。需要换个思路。虽然我的思路限制于此，因为本身对于算法和数据结构的不了解。导致了我虽然能抽象到出现括号，必然就要有括号去对应解除，但是抽象不到栈这种数据接口。有了栈就很自然了。

算法; 维护一个栈，遇到([ {时压栈，每次遇到 ) } ] 这三个括号时，检测栈定是否与相应括号相符和。符合的话弹栈，否则返回false。

伪代码：
1. n = strlen(s);
2. if(  n%2 ) return false;
3. char *stack =  malloc(n);
4. for(index=0, i = 0; i < n ;i++)        
5.     if( s[i] == '{'|| s[i] == '('|| s[i] == '[' )    
6.         stack[index++] = s[i];
7.     else
8.         if( ( s[i] ==')'&& stack[index-1]== '(') || ( s[i] ==']'&& stack[index-1]== '[') || ( s[i] =='}'&& stack[index-1]== '{'))
9.             index -- ;
10.        else return false;
11.  return index==0; 
```
