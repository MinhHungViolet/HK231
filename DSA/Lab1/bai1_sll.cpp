LLNode* addLinkedList(LLNode* l0, LLNode* l1) {
    LLNode* ptr = new LLNode(0, nullptr);
    LLNode* curr = ptr;
    int carry = 0;
    while (l0 || l1 || carry) {
        int sum = carry;
        if (l0) {
            sum += l0->val;
            l0 = l0->next;
        }
        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }
        carry = sum / 10;
        curr->next = new LLNode(sum % 10, nullptr);
        curr = curr->next;
    }
    return ptr->next;
}