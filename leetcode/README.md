##### Leetcode 刷题心得：
######  1. Two  Sum——哈希表。
头脑中需要有C语言的hashmap图，另外注意的细节需要见leetcode1 的详细计划。
![image](https://github.com/wsl8779752/leetcode/raw/master/images/1HashMap.jpeg) 
###### 2. Add Two Number——链表。
需要注意的是循环条件，只要l1||l2||carry_num有数，就需要循环。每次是进循环以后才开始分配内存。代码比较优美的地方在于对于 p 指针的处理如下：
            
        while( l1||l2||carry_num ){
        if(p==0) p = ans ;
        else {
          p->next = (struct ListNode*)calloc(1, sizeof(struct ListNode) );
          p = p->next ;                  
        }
###### 3. Longest Substring Without Repeating Character -滑动窗口。

    算法简介：
    核心的地方在于维护一个[i,j)型的滑动窗口，窗口内无重复字母。从 i = j = 0开始，j逐次右移。每次循环记录窗口长度ans = j-i+1，且对每一个j检查[i,j)窗口内包含S[j]字符与否。
    如果在窗口内的j'位置包含S[j]，说明最长的从i开始到j-1字符串找到，然后i右移跳过j'位置到j’+1。维护一个新的[i,j)滑动窗口。如果不包含，则j右移，新的[i，jnew）为[i,jold+1]。其中长度最长的窗口长度为正确的答案。
    
    小tips：
		    
        for( i=0 , j = 0; j < len; j++){
        if( hash[s[j]] ){
           i = max(i,hash[s[j]]);
        } 
        ans = max(ans,j-i+1);
        hash[s[j]] = j+1 ;
        }
        1. hash[s[j]] = j+1 是为了用 其他hash[s[j]]来表示滑动窗口里没有s[j].
        2. i =  max(i,hash[s[j]])。这里是max的原因在于，如果hash[[sj]]大于i，直接调到j’+1位置，因为hash[s[j]] = j+1。
        如果j‘出现在i 左侧，则i不能左跳，因为i的第一个字符就和[i,j)之间重复了。必须维持无重复字符的s[i,j)。

###### 4.  Median of Two Sorted Arrays —— 左右二分。 
将两个数组分别一分为二。用一个i表示分割位置。对于数组B 用j表示分割位置。 i的取值为[0,m],j 的取值为[0,n];


                left_A             i        right_A                            left_B             j        right_B
          A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]          A[0], A[1], ..., A[i-1]  |  A[i],, ..., A[n-1]    
		
        1.设置 imin = 0 , imax = m . i 在[imin,max] 之间搜索       
        2.while（ imin <= imax )
        	>> i = ( imin + imax ) / 2 , j = ( m + n + 1) / 2 - i .
        	>> 判断：
        		1.i > 0 and A[i-1] > B[j] , imax = imax -1 (i--)
        		2.i < m and A[i] < B [j-1] , imin = imin + 1 (i++)
        		3.i = 0 or A[i-1] <= B[j] or i = m or A[i] >= B [j-1] . 找到了正确的i和j，计算返回值。
        	  	先计算maxleft.max_left = A[i-1](j==0) or B[j-1](i==0) or max(A[i-1],B[j-1],if m+n 是奇数,直接返回maxleft               
        	  	m+n是偶数，需计算minright，minright = A[i]( j==n ) or B[j]( i==m ) or min(A[i],B[j]),返回 ( max_left + min_right ) / 2 .
            >> go to while
        
        小tips：
        1.在程序的最开始交换nums1和nums2使得m<=n ,既简化了程序边界条件测试，有了（ i>0 => j<n），也使得处理输入数组有一个为空的情况变得可能。 
        2.while循环的初始条件，是imin = 0， imax = nums1Size。while（imin<=imax) 后紧跟i = ( imin + imax ) / 2 , j = ( m + n + 1) / 2 - i
         保证了能够处理仅有m为0 的情况，如果m=n=0，则说明程序调用者SB，出错。
###### 5 . Longest Palindromic Substring - 动态规划 or expand around centor。
这里主要讲解动态规划。如果我们已知子串[i+1,j-1]是回文，那么子串[i,j] 是否是子串取决于 s[i]==s[j]? ,即： 		
        
        
        P(i,j) == (P(i+1,j-)&&s[i]==s[j]);
        P(i,i)=1;
        P(i,i+1) = (s[i]==s[i+1]);
        This is a perfect dynamic progarming problem.
        
        算法：
        len =  strlen(s);
        bool (*dyn)[len] = calloc( len*len,sizeof(bool));
        maxLen = 1 ;
        for i = 0 : len
        	dyn[i][i] = 1 ;
            if i>0 :            	
            	dyn[i-1][i] = ( s[i-1] == s[i] );
                if maxLen == 1 and dyn[i-1][i] : //记录长度为2的第一个回文起始索引和结束索引
           			maxLen ,ibegin,iend = 2,i-1,i; 
        for parlin_len = 3 : len+1
        	if maxLen < parlin_len -2:  //如果maxlen<n-2,本次扩展需要有n-2子串是回文，所以本次扩展无法进行。
            	//下次扩展需要n-1子串有回文，显然也不满足。所以继续扩展得不到更长的子串。free 内存后直接返回s[ibegin,iend ,\'0']
            	return s[ibegin  iend '\0'];
            i ,j = 0 parlin_Len + i -1;            
            while j < len:
            	dyn[i][j] =  (dyn[i+1][j-1] && s[i]==s[j]) ;
                if maxLen < parlin_len and dyn[i][i] //当前parlin_len子串没有被存储，存储子串
                    maxLen ,ibegin,iend = test_parlin_len,i,j
                 i++,j++   
		ans = malloc : (maxlen+1) * sizeof(cha) ;
        strncpy(ans,s+ibegin,maxLen);
        ans[maxLen] = '\0';
        free (dyn) ;
        return ans;  
###### 6 . ZigZag Conversion -考察细心和边界条件
		伪代码：
       if numRows == 1 return  s
       len = strlen( s );
       interval  = 2 *(numRows -1);
       index = 0 ；
        for i= 0 : numRows 
        	for( j = i,jump = 2*i; j < len ;j += jump)
            	ans[index] = s[j];
                jump  =  interval - jump;
                if( jump != 0 ) index++;
        ans[len] = '\0';        
        return ans
        tips: 
        1. jump  = interval - jump //非常精髓
        2. if(jump!= 0) index ++ 这条语句处理了最上和最下的row 只跳一步的情况。
		3. ans[len] = 0 这条语句不能集成到 j<= len 这条语句上。原因当输入是“AB” 2 时，第一次循环后，index = 1， j = 2， ans[1] =  (s[2]= '\0') ; 输出就变成了“A”。错误。

###### 7 . Reverse Integer- 数据类型和边界条件，负整型变量取余数和除法          
            
    
    伪代码：
    int digit_limit = INTMAX/10; 
    for digit = 0 ; num; num/=10; 
    reminder = num % 10;
    if( abs(digit) > digit_limit ||( abs(digit) == digit_limit &&(reminder<-8 || reminder > 7 )))
    return 0 ;
    digit *= 10;digit += reminder;
    return digit ;

    tips:
    1. 负数的取余与除法得到的都是负数，比如 -17/10 = -1， -17%10 = -7.我一直以为负数的取余数和除法得到的都是正数。
    所以负数的digit也可以直接相加。
    2. 关于溢出问题， C中int类型是32位的，范围是-2147483648到2147483647 .在本例中计算机只能hold 32  bit。所以
    必须在溢出之前做检测，必须要先达到214748364（INT_MAX/10)这个阈值，本次的digit *=10 才有可能溢出。这里又分为两种情况：
    1. if digit >  INT_MAX/10 值，直接溢出
    2. if digit == INT_MAX/10，如果digit是正数，加上>7 的数会溢出，如果digit是负数，加上<-8的数
    会溢出。边界条件由此而产生。            
    3. 关于leading zero 问题，其实只要digt×=10 ，得到的还是0 ，自动处理的leading zero 问题。
    4. 关于溢出问题，目前为止我们都是在预防溢出，实际上有一种更简洁的方法是让溢出发生。然后检测溢出后的的商是否和之前一致。
    代码如下：
        oldx=digit ； digit *=10;   digit += reminder;  
        if(digit/10 != oldx) return 0;
             
###### 8 . String to Integer (atoi）—— 非常烂的一个题目，考察啥？
		
     
    伪代码：
    len = strlen(str);
    for( i= 0; i< len and str[i] is whitespace ; i++ ); //jump over all leading whitespace
    if i == len return 0;  //str contains only whitespace characoters
    /*处理first none whitespace  + - or digit */
    if ( str[i] != '+' and str[i] != '-' and ( str[i] < '0'  or str[i]> '9' ) //the first nonwhitespace is not a valid number or optional plus or minus sign，return 0
        return 0；
    else if（ str[i]>='0' and str[i]<='9')
            if( i+1 == len ) return str[i]-'0';
    else :        	
        if( i+1 < len and str[i+1]>='0' and str[i+1]<='9'):
            if str[i] = '+': sign  = false ;
            else  : sign = true ;
            i++;
        else return 0;
    }

    for ans = 0; i < len and str[i] is digit; i++: //calculate ans untill reach a non_number character or end of string.
        ones_place = str[i]-'0';  //calcuate new ones_pace 
        if( abs(ans) > ans_limit || ( abs(ans) == ans_limit  && (ones_place > 8 or (sign = false and ones_place > 7) )) : 
        return sign ? INT_MIN : INT_MAX ;
        ans*= 10;
        ans += ones_place ;
    return ? -asn : ans ;

    tips（或者编程中错误的地方）
    1. sign 的默认值没有设定为False ，没设定的话，给定的字符串中不出现 + - 符号，那么实际值是正值，但局部变量可能会
    自动分配为false。导致返回值符号相反。
    2. 最后的return 没有考虑符号， return sign？ -ans ： ans
    3. 溢出检测也设计的比较麻烦，简洁代码：
     oldans = ans ； ans×=10 ；ans+= ones_place ; if( oldans!= ans ) return sign? INT_MIN : INT_MAX 就行了。
        
###### 9. Palindrome Number - 考察3种边界条件
        
     
    伪代码：（比较简单所以直接贴源代码）:
    bool isPalindrome(int x) {
    int reverse_num ;
    if ( x < 0 || ( x!=0 && x%10 ==0) ) return false;   
    reverse_num = 0 ;
    while( reverse_num < x ){
         reverse_num = reverse_num*10 + x%10;
         x/=10 ;
    }
        return reverse_num==x || reverse_num/10==x ; 
    }

    Tips：
    1.0 是parlin
    2.结尾是0 可以被10整除的情况，但不包含0（因为0是parlin）。无论如何都不可能是0。因为原num的最高位不可能是0.但如果
    用reverse_num 与 num比，先导0被去掉，数“1210”会reverse成12 导致算成是parlin。
    3.负数的情况，绝不是 -1  parlin 1-.但算法会算成是，所以去掉
    4.会溢出吗？不会，因为数只有一半的原数位，根本不可能溢出。 
    5.return revere_num = x || reverse_num/10 == x非常精髓，我有类似想法，但没有转化成代码，转化成这样的代码
    非常简洁。
###### 11. Container With Most Water - 智商？？
		
     算法分析：
        max_area = min( height[i0],height[len-1]) *heightSize;
        1.头尾指针i，j分别指向 0 和 len-1。
        2.计算 act_area =  min( height[i],height[j] ) * (j-i+1)，如果act_area > maxarea，更新area
        3. 移动i或者j：假设 height[i] < height[j] ，那么如果j减小，面积肯定会缩小，因为短板在左边。所以应该指针往可能增加
        面积的方向移动，毫无疑问移动短板。移动短板后，到2 。直到 i = j 循环结束。
        
    伪代码：
    max_area = 0;        
    i,j = 0,heightSize-1 ; 
    while( i < j) {
        min = min( height[i],height[j]);
        area =  min *(j-i) ;
        if( area > max_area) max_area = area ;
        if(  height[i] < height[j])  while( ++i < j && height[i]<= min );
         else   while( i < --j && height[j]<= min );
    }
    return max_area ;
    
    Tips:
    计算 area 公式 中area = min * (j-i+1) 不对，因为宽度是j-i。这里在第一次集成错了。其他全对。自己想当然的认为计算的是i，j之间有多少数。

###### 14 .  Longest Common Prefix -- 循环比较
		
        伪代码：
        if ( strsSize == 0 ) return NULL ;
        len0 = strlen( str[0] ) ;
        ans  =  malloc ( sizeof(char) * (len0+1));
        strcpy( ans , str[0] );
        for( i = 1; i< strSize ; i++ ){
        	j = 0;
            while(  j < len0 && ans[j] == str[i][j] );
            if(j ==0 ) return "";
            ans[j] = '\0';
            len0 = j ;           
        }
        return ans ; 
        
        但这种算法通过不了timelimit : 通过时间测试的算法如下。感觉连个这差不太多.
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
        
        Tips:
        如果来的都是空字符串，返回值不应该是NULL，而应该是一个指向空字符串的指针 ，例如“”。
        
###### 15 . 3Sum  - 考察循环、边界条件、提速条件：
        
        算法分析：
        1. 排序
        2. 用3重指针进行寻找数。

        伪代码：
        sort array；
        numsSize < 3 return NULL;
        int **ans = calloc(1,sizeof(int * ));        
        add_of_last_twonum = nums[len-1} + nums[len-2]；
        for(*returnSize=0， begin = 0 ; begin < len-2 ; begin++)
            if（ (begin && nums[begin] == nums[begin-1]) || ( nums[begin} + add_of_last_twonum < 0  ) ) continue ;
            l = begin+1 ,r = len-1; 
            rest = - nums[begin];
            if( nums[begin+1] + nums[begin+2) > rest ) return ans ;           
            while( l < r ):           	 
            if ( nums[l] + nums[r] < rest ) 
            while ( ++l < r && nums[l] == nums[l-1] )  ;
            else if( nums[l] + nums[r] > rest )  while ( l < --r && nums[r] == nums[r+1] )  ;
            else  :
                add new_solution to answer；(refer to Tips) 
                while ( ++l < r && nums[l] == nums[l-1] )  ;j--;
            return ans
            
        Tips：
        1.加速条件：
            1. 内循环中跳过重复的值 while ( ++l < r && nums[l] == nums[l-1]
            2. 外循环中用了三个技巧来加速： 跳过重复值 ；假如num[begin] + num[end-2]+ num[end-1] < 0 ,说明
            3begin 太小，直接continue ；  假如num[begin] + num[bein+1] +num[begin+2] > 0。
            后续的数无论如何都找不到=0，直接返回ans
        2. 本例中不包含返回值申请内存用于返回，实际上C语言申请内存用于返回也是一门学问。详细代码：
        if( *returnSize )
          ans = realloc(ans, sizeof(int *)*( *returnSize+1) );
        ans[*returnSize]  = malloc( sizeof(int) *3 );
        ans[*returnSize][0] = nums[begin]; 
        ans[*returnSize][1] = nums[l];
        ans[*returnSize][2] = nums[r];
        (*returnSize) ++;
        注意点有2个，
        1. 使用指针数组ans[*returnSize]指向答案,
        2.（*returnSIze）最后自增，但分配ans[]在前，所以：
        ans = realloc(ans, sizeof(int *)*( *returnSize+1) 

16 .3Sum Closest - 继续考察循环与边界条件：
		  
    算法
    3重指针，头指针begin 从 0 到 end-2；内循环左右指针夹逼即可。
    
    伪代码：

    if ( numsSize < 3) return 0;    
    sort_use_heap(nums,numsSize);// sort array in increasing  order
    
    /*if the smallest number in array is smaller than target , we find the nearest 3sum which is 
    nums[0] + nums[1] +nums[2]*/      
    if ( nums[0] >= 0 && target <= 0 ) 
    	return (nums[0] + nums[1] +nums[2]); 
    
    /* the same idea as smallest number in array ,but this time is the biggest one in array */
    if( nums[numsSize -1] <= 0 && target >= 0)  
    	return nums[numsSize -3] +nums[numsSize -2]+nums[numsSize -1];
    
    for(ans = nums[0] + nums[1] + nums[2], begin = 0 ; begin < numsSize -2 ;begin ++){
        /*if the smallest 3sum under a given "begin" is bigger than target, the cloest 3sum in this circulation finded  */
        if (  (temp = nums[begin] + nums[begin+1] + nums[begin+2] ) > target   ) { 
            ans = temp-target < abs(ans-target) ? temp : ans ;
            continue ;
        } 
        /*if the biggest 3sum under a given "begin" is smaller than target, the cloest 3sum in this circulation finded  */
        if(  (temp = nums[begin] + nums[numsSize-2] + nums[numsSize-1] ) < target  ){
            ans = abs(temp - target) < abs(ans-target) ? temp : ans  ; 
            continue;
        }           
        l =  begin+ 1, r = numsSize - 1;
        while ( l < r ) 
            if( (temp = nums[begin] + nums[l] +nums[r] ) < target )
                ans = abs( temp - target) < abs( ans - target) ? temp : ans;
                while (++l < r && nums[l]== nums[l-1] ); //jump over repeated nums[l]                   
            else if ( temp > target)
                ans = temp-target < abs(ans-target) ? temp : ans;
                while( l< --r && nums[r] == nums[r+1]v);//jump over repeated nums[r]                
            else return temp;    
    return ans;
17 . Letter Combinations of a Phone Number - 递归
		 
	算法： 使用递归，只要没达到最后一列，则函数写自己，调用下一层。如果达到最后一行，写自己，并且复制答案进入ans。简单逻辑是这样。需要注意的是如果出现0 和 1，则认为输入是失败的。返回NULL
    
    伪代码：
    const char *letters[10] = { " ","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" }; //全局常量
    
    char** letterCombinations(char* digits, int* returnSize)：
        if( digit == NULL || ( len = strlen( digit ) ) == 0 ) return NULL;
        for (*returnSize =1, i  = 0 ; i< len ; i ++ )
            if   ( j = digit[i] - '0') < 2  or j > 9  return NULL；
            *returnSize = (*returnSize) * strlen(letters[j]);
        char *temp = malloc( sizeof(char)* (len+1)) ;
        char **ans  = malloc(sizeof(char*)*（*returnSize)) ;
        temp[len] = '\0'; //all ans is ended by '\0', we add '\0' to end of temp here, thus we don't need to add '\0' every time we copy temp to ans.
        pindex  = 0 ;
        add_ans (digits, 0,len-1,&pindex,temp,ans) ;
        return ans ;
    
    add_ans原型 :
    void add_answer( char *digits ,int rows , int len, int *pindex, char *temp, char **ans){
        char *act_s; 
        if( rows < len ) 
            act_s = letters[ digit[rows] - '0'] ;
            while(  *act_s )
                temp[rows] = *act_s++;
                add_ans ( digits, rows+1,len,pindex,temp,ans) ;
         else
            act_s = letters[ digit[rows] - '0'] ;
            while(  *act_s )
                temp[rows] = *act_s++;         
                ans[*pindex] = malloc(sizeof(char)*(len+1));	
                strcpy = (ans[*pindex],temp);
                (*pindex)++;
           return   ; 
    Tips:
     1. 在 letterCombinations()函数里调用add_ans,注意第一次的实参是len-1。这和我们最后的函数有关，最后的函数是row 到len-1 就开始了复制函数。
     2. 整体思路上的变化，处理 <2 和 >9 的数，直接返回NULL，因为认为这是不符合输入要求的数字。那么剩下的都是2-9的数字，可在函数里计算需要的存储空间和返回字符串长度。然后在add_ans函数里直接将数据填入即可。
     3. 在letterCombinations()里出现了，*temp[rows] 的失误，说明还是对这种递归调用不熟悉。或者说对整体思路把握不准确。
     4. 整体逻辑上大的错误没有，虽然把代码copy到codeblock才解决问题，但整体上还是不错的。
###### 18. 4Sum - 循环

```
算法:
三重循环（4指针）在数组a[]中找组合数,    
1. 外循环begin =  [0,n-4],  
2. 中循环second =[ i+1 , n-3].  
3. 内循环开始用左指针left指向j+1 ,右指针right指向n-1.计算sum = a[begin] + a[seond] + a[left] + a[right] .
	a. 如果sum < target. left指针右移;
	b. 如果sum > target . right指针左移;
	c. 如果sum =  target . 找到合适的组合数.跳过重复的 	a[left] 与 a[right] (left++ right-- 直到跳过重复,这样可以保证返回数据的唯一性)
	7. 继续执行循环计算sum
4 . 同理中层循环a[second]每次都需要跳过重复的. 外层循环也需要跳过重复的a[begin]. (这样做是为了保证返回数组的唯一性) .  
  
大致上的思路就是这样.一些小的trick是
1. 如果i,j 确定后, a[i] + a[j] + a[j+1] + a[j+2] > target .说明此种i,j 组合已经不可能再找到组合数. 直接break 中层组合,i 后移即可.
2. 如果i,j 确定后,a[i] + a[j] + a[n-2] + a[n-1] < target.说明此时任何 j 都不满足条件. 必须增大j 才有可能.直接continue循环. 
3. 每次不在内循环中计算 sum . 而是在中循环中计算 rest = target - a[i] + a[j] . 在内循环中替换判断条件 sum > target ? 为 rest > a[left] + a[right] ? 可以节省一些程序运行时间.   
   
##### 伪代码:
1. set *returnSize to 0
2. if ( n = nums.len) < 4 return NULL
3. sort nums[] //from small to big
4. for begin  = 0 to n-3 ; begin++
5.	 if begin!=0 && nums[begin]== nums[begin-1] continue
6.	 for second = begin+1 to n-2 ;second ++
7.		if  second != begin+1 && nums[seoncd] == nums[second-1] continue
8.		rest = target - nums[begin] - nums[second]
9.		if nums[second+1]+nums[second+2] > rest     break; //更换begin second
10.	   if nums[n-2] + nums[n-1]  < rest      continue; //增大second
11.	   left = second +1
12.	   right = n -1 
13.	   while left < right
14.	       sum =  nums[left] + nums[right]
15.	       if sum < rest :  left++
16.	       else if sum > rest : right--
17.	       else	          
19.	          realloc a size of (*returnSize+1)*int memory for ans_array( type array of pointer's pointer)
20.	          ans_array[*returnSize  ] = malloc 4*int piece of memory for the finded elements 
21.	          copy finded elements to the  allocated piece of memory
22.	          do left++ 	until ( left < rgiht && nums[left] != nums[left-1])
23.	          do right--    until ( left < right && nums[right]!= nums[right+1])
24.              *returnSize += 1;
25. return ans_array

Tips:
1. 在外层的for循环少了一个大括号，导致整个程序逻辑不对
2. 在开始malloc 存储的时候，脑子抽筋malloc 了一个 char× 的 ans[] 指针数组，实际上答案是int × ，导致错误
3. 在处理19 realloc a size of memory 的时候，犯了一个错误， 应该是realloc(ans ,（*returnSize+1）* sizeof(int) ) ，我写成了 realloc(ans ,(*returnSize+1) ),错误。另外需要注意是×returnSize+1 个 sizeof（int）内存。
``` 
###### 19.Remove Nth Node From End of List 链表

``` 
算法:
算法有两种，
1.第一种需要遍历链表2遍，找到链表长度L，然后移除顺数第 L-n+1个节点。也就是说讲顺数第 L-n 的nexet 指向L-n+2节点。这种算法比较简单。但需要遍历两次链表。
2.第二种算法只需要遍历一遍列表，遍历的时候使用first和second两个指针，使得frist指针指向领先second指针 n+1个节点处。然后first 和second指针同时增加，知道second 到达末尾NULL，此时first指针刚好指向L-n节点，那么将L-n节点直接指向L-n+2 节点即可。

伪代码：
1. first , second =  head，head；
2. while( second != NULL )
3.  	second = second->next;
4.  	if( n -- < 0 ) first = first->next ;
5. if( n == 0 )  head = head->next ; free(first);	
5. else 
6. 		second = first->next ;
7. 		first->next  = second->next;
8. 		free(second);
9. 	return head	 	

Tips:
1. 我原始的程序中，有两个while，一个循环使得first领先second n+1 个节点，第二个循环再使得first到末尾。这样的话程序还要在第一个循环中提前判断是不是刚好需要删除根节点，代码非常不优雅。
2. 采用上述的伪代码后，程序很优雅并且巧妙。但需要注意是 n-- < 0 ,也就是说领先n+1 。 另外在free内存的时候，如果不是根节点，要注意先使得second = first->next; 如果是sceond= fist,后面代码一样的话，会free next->next->next的节点。 j
```

###### 20. Valid Parentheses

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

算法; 维护一个栈，遇到([ {时压栈，每次遇到 ) } ] 这三个括号时，检测栈顶是否与相应括号相符合。符合的话弹栈，否则返回false。

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
13.  return index==0; 
```
###### 21. Merge Two Sorted Lists 
```
算法：
很简单，就是循环比较　l1的数据和l2 的数据，哪个小就让 p->next 指向哪个，然后 p ＝ p->next。
并且小的数据往前移动到　next节点。总体来讲，算法容易，但是需要考虑的特殊情况比较多。
1. 如果两个节点都是空节点
2. 两个节点中有一个为空节点

考虑上述两种特殊情况的伪代码：
MergeTwoLists  (listNode* l1,  ListNode* l2) :  
1.if l1 == NULL :  return l2;
2.if l2 == NULL :   return l1;
3.while l1 &&l2  :
4.     if l1->val <  l2->val :
5.            if p == NULL 
6.                p = l1 ;  l1 = l1->next; ans = p;
7.           else :
8.                p->next = l1 ; l1 = l1->next; p = p->next;        
9.     else:
10.            if p == NULL:                 
11.                p = l2;l2 = l2->next;ans = p;
12.            else :
13.                p->next = l2 ;l2  = l2->next; p = p->next ;         
14.p->next = l1 == 0? l2:l1;
15.return ans;   
代码里将两种特殊边界条件合二为一了，如果有一个空节点，就返回另外一个节点。如果两个为空，自然返回的也是空节点。
另外就是代码里有一种特殊情况，就是第一次建立节点的时p指向l1,而不是 p1->next指向l1。这个exception造成了代码里的好多if 和 else,显得不简洁优美。考虑使用一个无用节点使得p先指向无用节点，然后最后返回无用节点的next 节点即可。

伪代码２：
1. ListNode* mergeTwoLists( ListNode* l1,  ListNode* l2)
2.     struct ListNode temp = {0,0};
3.     struct ListNode *p= &temp ;
4.     while( l1 &&l2 ) {
5.         if( l1->val <  l2->val ){
6.             p->next = l1 ;
7.             l1 = l1->next;
8.             p = p->next;
9.         }
10.         else{
11.             p->next = l2 ;
12.             l2  = l2->next;
13.             p = p->next ;
14.         }
15.     }
16.     p->next= l1 == NULL ? l2:l1;
17.     return temp.next ;    

惊喜的发现，竟然最开始的空节点也包含在了这个代码里，非常简洁优雅。
```
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
###### 24 Swap Nodes in Pairs 
```
算法：交换head和head->next(headPair)的指向关系，并且使得前一节点指针p->next指向headPair,恢复现场，使得head->head->next.
丑陋代码1:
 1 struct ListNode* swapPairs(struct ListNode* head) :                                                                                                                                                
 2     struct ListNode *p,*headPair;
 3     struct ListNode temp = {0,NULL} ;
 4     if(head == NULL || head->next == NULL) return head ;
 5     p = &temp ;
 6     while(head && head->next):
 7         headPair = head->next;
 8         head->next = headPair->next;
 9         headPair->next  = head ;
10         p->next = headPair ;
11         p = head ;
12         head = head->next;
13     return temp.next ;

Tips: 上述代码编写过程中，逻辑没什么问题，只是第一版中没有加最开始的 
if(head == NULL || head->next == NULL) return head ;
导致程序处理输入[] 和[1]时会有问题，访问了不该访问的内存。加上了虽然解决了，但是显得代码比较LOW;

消除特殊情况的代码2:
 1 struct ListNode* swapPairs(struct ListNode* head):                                                                                                                                                   
 2     struct ListNode *p,*headPair;
 3     struct ListNode temp = {0,head};  
 4     p = &temp ;   
 5     while(head && head->next):
 6         headPair = head->next;
 7         head->next = headPair->next;
 8         headPair->next  = head ;
 9         p->next = headPair ;
10         p = head ;
11         head = head->next;
12     return temp.next ;

tips: 消除特殊情况的代码只需要将初始化时的temp.next = head 即可。
```
###### 18. 4Sum - 循环

```
算法:
好像就是迭代两个两个互换么，没啥技巧，不明白为啥是非常难的。

代码:
 1 struct ListNode* reverseKGroup(struct ListNode* head, int k) {                                                                                                             
 2     struct ListNode root, *previousEnd ,*temp ,*p ;                                               
 3     int i, j;                                                                                   
 4     root.next = head ;                                                                         
 5     p = &root ;                                                                               
 6     for(j= 0; p = p->next ;j++ ) ;                                                             
 7     p = &root ;                                                                              
 8     while((j-=k )>= 0 ){                                                                                                   
 9         previousEnd = p ;                                                                                                             
10         for( head = p->next, p=head,i=1;i<k;i++){                                                                                                                           
11             temp = head ;                                                                                                                                          
12             head = p->next ;                                                                                                                                              
13             p->next =  head->next ;                                                                                                                    
14             head->next = temp ;                                                                                                                                           
15         }                                                                                                                                                        
16         previousEnd->next = head ;                                                                                                                              
17     }                                                                                                                                   
18     return root->next ;                                                                                                                                         
19 }                                

Tips:
1. 其实整个逻辑都对，关键是理解错了题目意思，题目是要reverse 所有的Ｋ组节点，main.c里的代码
只reverse了一组节点，导致逻辑错误。
2. 其实这道题目坐下来，对循环有了比较深刻的理解。循环的结束如果能保持和循环开始的状态一致，那
么就是一个好的循环。这种思想在这里体现的尤为淋漓尽致。
3. 使用根节点使得整个函数没有了特殊情况，非常简洁优雅。
```
![image](https://github.com/wsl8779752/leetcode/raw/master/images/25Node.png) 
