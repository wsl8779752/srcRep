###### 21. Valid Parentheses
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
