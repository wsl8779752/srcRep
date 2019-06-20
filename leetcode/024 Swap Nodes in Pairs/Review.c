struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode *p,*headPair;
    struct ListNode temp = {0,head};  
    p = &temp ;   
    while(head && head->next){
        headPair = head->next;
        head->next = headPair->next;
        headPair->next  = head ;
        p->next = headPair ;
        p = head ;
        head = head->next;
    }    
    return temp.next ;
}
