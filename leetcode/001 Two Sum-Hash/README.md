##### 解法：
这道题目可以有两种解法。
1. 使用双重循环，外层循环i从 0 到len-2,内层循环j从i+1 到numsSize-1 找合适的数。这大约需要1+2+...+n-1 =  n^2 /2 次步骤，也就是说时间 o(n^2).
2. 使用HASH表，为O(n)时间长度。


下面给出C 语言哈希表的详细解决方案：
##### C 语言解决方案


![C语言解决方案](/home/wei/Downloads/hash_map.jpeg "C 语言详细方案")

##### tips:
1. 在hash_get 和 hash_set 函数里的 hash 都要用 绝对值，即 abs(num)%  hashmap->size
2. hash_get 和 hash_set 函数里的 hash++ 的时候注意不要溢出数组边界 。   
        if( hash < hashmap->size-1)
                hash++;
        else hash= 0;
        
3. 在hash_set 函数里要先请求内存，再将 table[hash] 指向 请求的内存。
4. hash_get 找不到数时，返回 -1 ，用来区分出现答案是 nums[0] 的情况.
