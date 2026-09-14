/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        

        ListNode* temp=head;

        int length=0;
        while(temp){
            length++;
            temp=temp->next;
        }
        cout<<length;
        if(length==1){
            return NULL;
        }
        if(length==n){
            return head->next;
        }
        length=length-n-1;
        temp=head;
        while(length>0){
            temp=temp->next;
            length--;
        }
        temp->next=temp->next->next;
        return head;
    }
};