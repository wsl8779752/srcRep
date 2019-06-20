struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *ans ,*p= NULL ;
    if( l1 == NULL )   return l2;
    if( l2 == NULL )   return l1;
    while( l1 &&l2 ) {
        if( l1->val <  l2->val ){
            if( p == NULL ){
                p = l1 ;
                l1 = l1->next;
                ans = p;
            }
            else{
                p->next = l1 ;
                l1 = l1->next;
                p = p->next;
            }
        }
        else{
            if( p == NULL){
                p = l2;
                l2 = l2->next;
                ans = p;
            }
            else{
                p->next = l2 ;
                l2  = l2->next;
                p = p->next ;
            }
        }        
    }
    if( p == 0 )
        return l1==0 ? l2:l1 ;
    else{
        p->next = l1 == 0? l2:l1;
        return ans;   
    }       
 }
