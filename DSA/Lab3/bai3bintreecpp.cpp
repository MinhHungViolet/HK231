int treePathsSumUtil(BTNode *root, int value) 
{ 
    if (root == NULL) return 0; 
 
    value = (value*10 + root->val); 
 
    if (root->left==NULL && root->right==NULL) 
    return value; 
 
    return treePathsSumUtil(root->left, value) + 
        treePathsSumUtil(root->right, value); 
} 


int sumDigitPath(BTNode* root) {
    return treePathsSumUtil(root, 0); 
}