LLNode* rotateLinkedList(LLNode* head, int k) {
    if (head == nullptr || head->next == nullptr || k == 0) {
        return head;
    }
    int len = 1;
    LLNode* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
        len++;
    }
    k %= len;
    if (k == 0) {
        return head;
    }
    LLNode* newTail = head;
    for (int i = 0; i < len - k - 1; i++) {
        newTail = newTail->next;
    }
    LLNode* newHead = newTail->next;
    newTail->next = nullptr;
    tail->next = head;
    return newHead;
}