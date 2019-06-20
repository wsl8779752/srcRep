struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* front = head;
    struct ListNode* behind = head;

    while (front != NULL) {
        front = front->next;

        if (n-- < 0) behind = behind->next;
    }
    if (n == 0) 
    {
        front = head ;   
        head = head->next;
        free (front)  ;
    }
    else{
        front = behind->next;      
        behind->next = behind->next->next;
        free(front) ;        
    }
    return head;
}
