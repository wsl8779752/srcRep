/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode root, *previousEnd ,*temp ,*p ;
    int i, j;
    root.next = head ;
    p = &root ;
    for(j= 0; p = p->next ;j++ ) ; 
    p = &root ; 
    while((j-=k )>= 0 ){
        previousEnd = p ;
        for( head = p->next, p=head,i=1;i<k;i++){
            temp = head ;
            head = p->next ;
            p->next =  head->next ;
            head->next = temp ;
        }
        previousEnd->next = head ;
    }
    return root->next ;
}
