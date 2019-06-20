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

