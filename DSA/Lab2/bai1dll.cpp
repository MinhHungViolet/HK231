template <class T>
void DLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    Node* newNode = new Node(e);
    if (head == nullptr){
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
    }
    count++;
}

template<class T>
void DLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */ 
    if (index < 0 || index > count){
        throw std::out_of_range("Index out of range");
    }
    if (index == count){
        add(e);
        return;
    }
    Node* newNode = new Node(e);
    if (index == 0){
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
    } else{
        Node* curr = head;
        for (int i = 0; i < index - 1; i++){
            curr = curr->next;
        }
        newNode->next = curr->next;
        newNode->previous = curr;
        curr->next->previous = newNode;
        curr->next = newNode;
    }
    count++;
}

template<class T>
int DLinkedList<T>::size() {
    /* Return the length (size) of list */ 
    return count;
}