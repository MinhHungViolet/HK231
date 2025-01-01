// Merge two sorted lists
ListNode* mergeLists(ListNode* l1, ListNode* l2) {
    ListNode node(0);
    ListNode* tail = &node;

    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    tail->next = l1 ? l1 : l2;

    return node.next;
}

// Sort an unsorted list given its head pointer
ListNode* mergeSortList(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }

    ListNode* slow = head;
    ListNode* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode* mid = slow->next;
    slow->next = nullptr;

    return mergeLists(mergeSortList(head), mergeSortList(mid));
}