int singleChild(BSTNode* root) {
    if (root == nullptr) {
        return 0;
    }
    int count = 0;
    if ((root->left == nullptr && root->right != nullptr) || (root->left != nullptr && root->right == nullptr)) {
        count++;
    }
    count += singleChild(root->left) + singleChild(root->right);
    return count;
}