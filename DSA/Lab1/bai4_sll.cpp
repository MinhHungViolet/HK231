template <class T>
T SLinkedList<T>::removeAt(int index)
{
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index out of range!");
    }
    T removedValue;
    if (index == 0) {
        Node* temp = head;
        head = head->next;
        removedValue = temp->data;
        delete temp;
    } else {
        Node* prev = head;
        for (int i = 0; i < index - 1; i++) {
            prev = prev->next;
        }
        Node* temp = prev->next;
        prev->next = temp->next;
        removedValue = temp->data;
        delete temp;
        if (index == count - 1) {
            tail = prev;
        }
    }
    count--;
    return removedValue;
}

template <class T>
bool SLinkedList<T>::removeItem(const T& item)
{
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data == item) {
            if (prev == nullptr) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            if (curr == tail) {
                tail = prev;
            }
            delete curr;
            count--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

template<class T>
void SLinkedList<T>::clear(){
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}