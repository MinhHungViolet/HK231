template <class T>
void SLinkedList<T>::bubbleSort() {
    if (this->size() == 0 || this->size() == 1) return;

    //Node* sorted = this->head;
    for(int i = 0; i < this->size() - 1; i++){
        bool isSwapped = false;
        Node* sorted = this->head;
        Node* start = sorted;
        for(int j = 0; j < this->size() - i - 1; j ++){ 
            Node* p1 = start;
            Node* p2 = p1->next;
            if(p1->data > p2->data){
                T temp = p1->data;
                p1->data = p2->data;
                p2->data = temp;
                isSwapped = true;
            } 
            start = start->next;
        }
        sorted = sorted->next;
        if(isSwapped){
            this-> printList();
        } 
        else break;
    }
}