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
4Sum IN nums[]
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
17.	       else18.	          
19.	           realloc a size of (*returnSize+1)*int memory for ans_array( type array of pointer's pointer)
20.	          ans_array[*returnSize  ] = malloc 4*int piece of memory for the finded elements 
21.	          copy finded elements to the  allocated piece of memory
22.	          do left++ 	until ( left < rgiht && nums[left] != nums[left-1])
23.	          do right--    until ( left < right && nums[right]!= nums[right+1])
24.               *returnSize += 1;
25. return ans_array

Tips:
1. 在外层的for循环少了一个大括号，导致整个程序逻辑不对
2. 在开始malloc 存储的时候，脑子抽筋malloc 了一个 char× 的 ans[] 指针数组，实际上答案是int × ，导致错误
3. 在处理19 realloc a size of memory 的时候，犯了一个错误， 应该是realloc(ans ,（*returnSize+1）* sizeof(int) ) ，我写成了 realloc(ans ,(*returnSize+1) ),错误。另外需要注意是×returnSize+1 个 sizeof（int）内存。

```
