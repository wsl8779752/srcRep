### 4.Median of Two Sorted Ayyays
给定两个排序数组,找出其中的中位数.  
例１：  
```
nums1 = [1, 3]  
nums2 = [2]   
The median is 2.0  
```
例子2:
```
nums1 = [1, 2]　　　
nums2 = [3, 4]  
The median is (2 + 3)/2 = 2.5
```
##### 伪代码:
1. 设置 imin = 0 , imax = m . i 在[imin,max] 之间搜索
2.  i = ( imin + imax ) / 2 , j = ( m + n + 1)  / 2 - i .
3.  判断
	1. i > 0 and A[i-1] > B[j] , imax = imax -1 (i--) 
	2. i < m  and A[i] < B [j-1] , imin = imin + 1 (i++)  
	3. i = 0 or A[i-1] <= B[j] or i = m or A[i] >= B [j-1] . 找到了确定的i. 确定返回值, 如果m+n 是奇数,返回 max_left ,如果 m+n 是偶数,返回 ( max_left + min_right ) / 2 .
	4. go to 2
