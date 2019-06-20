## [002 Add two number in linklist](https://leetcode.com/problems/add-two-numbers/description/)
其实逻辑上很简单，就是一个主循环判断是否存在 p1||p2||进位，如果存在，则新建链表，将加数写进新链表即可。

#### 本人原始代码
本人原始的代码里考虑了很多特殊情况，比如
1. 是否有加数存在作为一种情况if(   l1 && l2  )
2. 是否有进位作为一种特殊情况 else 
3. 第一进入考虑记录初始节点的问题  
  
其实这种方法虽然运行速度快，但带来了代码的不够简洁。可读性变差。
```
while( l1 || l2 || carry_nums )
  {
     new_node = calloc(1,sizeof(struct ListNode)) ;    
    
      if(   l1 && l2  )
      {  
          new_node->val = (l1->val+ l2->val +carry_nums)%10;
          carry_nums= (l1->val+ l2->val +carry_nums)/10 ;      
      } 
      else 
      {
          p= l2== NULL? l1 :l2 ;
          if( p )
          {    
            new_node->val= (p->val+ carry_nums)%10;
            carry_nums =  (p->val+ carry_nums)/10 ;
          }
          else
          {    
              new_node->val= carry_nums;
              carry_nums = 0   ;
          }  
      }   
      if(l1)
        l1 = l1->next;
      if(l2)
        l2 = l2->next ;
      
      if(i==0)
      {  
         return_node = new_node ;      
      }
      else previous_node->next = new_node;
      
      if( i<30 ) i++;
      else    i=1; 
      previous_node =  new_node ;  
  }    
  return  return_node ;
}
```
其实可以更简单的判断，建立一个p=0；主循环判断条件还是一样，将特殊情况合并。主要的代码语句是

```
p->val =  (l1? l1->val:0) + (l2? l2->val:0) + carry_num
```
在这条代码里，将判断和进位放到一起了，非常完美。

``` 
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
  struct ListNode* p=0,*ans = calloc(1, sizeof( struct ListNode));
  int carry_num =0 ;

  while( l1||l2||carry_num ){
      if(p==0)
      {
          p = ans ;
      }
      else
      {
          p->next = (struct ListNode*)calloc(1, sizeof(struct ListNode) );
          p = p->next ;                  
      }
      p->val =  (l1? l1->val:0) + (l2? l2->val:0) + carry_num ;
      carry_num = p->val /10;
      p->val %=10 ;      
      l1 = l1? l1->next : 0;
      l2 = l2? l2->next : 0;
  }
   return ans;   
}
```
