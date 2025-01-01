int treeHeight(Node* root){
    if(root == NULL){
        return 0;
    }
    int lHeight = treeHeight(root->pLeft);
    int rHeight = treeHeight(root->pRight);

    return max(lHeight+1, rHeight+1);
}

void printPostorder(Node* root){
    if(root == NULL) return;

    printPostorder(root->pLeft);
    printPostorder(root->pRight);
    cout<< root->value << " ";
}

void printInorder(Node* root){
    if(root == NULL) return;

    printInorder(root->pLeft);
    cout << root->value<< " ";
    printInorder(root->pRight);
}

void printPreorder(Node* root){
    if(root == NULL) return;

    cout<<root->value<< " ";
    printPreorder(root->pLeft);
    printPreorder(root->pRight);
}

int getHeight() {
    // TODO: return height of the binary tree.
    return treeHeight(this->root);
}

string preOrder() {
    // TODO: return the sequence of values of nodes in pre-order.
    printPreorder(this->root);
    return "";
}

string inOrder() {
    // TODO: return the sequence of values of nodes in in-order.
    printInorder(this->root);
    return "";
}

string postOrder() {
    // TODO: return the sequence of values of nodes in post-order.
    printPostorder(this->root);
    return "";      
}