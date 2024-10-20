// Function to find the middle node of a linked list
// this contains the edge cases also
struct ListNode* middleNode(struct ListNode* head) {
    // Check if the list is empty or has only one node
    if (head == NULL || head->next == NULL) {
        return head;
    }

    struct ListNode* fast = head;
    struct ListNode* slow = head;

    // Use two pointers to find the middle node
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next; // Move fast pointer two steps
        slow = slow->next;       // Move slow pointer one step
    }

    return slow; // Slow will be at the middle node
}