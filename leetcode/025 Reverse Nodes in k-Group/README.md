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
