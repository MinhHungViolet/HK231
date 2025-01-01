int kthSmallest(BSTNode* root, int k) {
    stack<BSTNode*> s;
    BSTNode* curr = root;
    int count = 0;
    while (curr != nullptr || !s.empty()) {
        while (curr != nullptr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        count++;
        if (count == k) {
            return curr->val;
        }
        curr = curr->right;
    }
    return -1; // k is out of range
}