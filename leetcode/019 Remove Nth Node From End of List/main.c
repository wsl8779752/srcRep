struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* first ,*second;
    int i;  
    first = head;
    for(second = head, i=0 ; i<n+1 ;i++ ){
        if( second = NULL ) { //删除根节点的特殊情况
            head =  first->next ;
            free(first) ;
            return head ;
        }
        second = second->next;  //second指针领先first n+1个节点 	
    }
    while( second != NULL){
        second = second->next ;
        first = first->next;
    }
    second  = first->next->next ;
    free(first->next);
    first->next =  second;
    return  head ;		   
}
