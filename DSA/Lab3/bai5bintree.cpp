int sumRecur(Node* root){
    if(root == NULL) return 0;
    else if(root->pLeft == NULL && root->pRight == NULL){
        return root->value + sumRecur(root->pLeft) + sumRecur(root->pRight);
    }
    else return sumRecur(root->pLeft) + sumRecur(root->pRight);
}
//Helping Functions
int sumOfLeafs(){
    //TODO
    return sumRecur(this->root);
}