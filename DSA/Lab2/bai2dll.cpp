template<class T>
DLinkedList<T>::DLinkedList() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template<class T>
DLinkedList<T>::~DLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template<class T>
void DLinkedList<T>::add(const T &e) {
    Node* newNode = new Node(e);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}

template<class T>
void DLinkedList<T>::add(int index, const T &e) {
    if (index < 0 || index > count) {
        throw std::out_of_range("Index out of range");
    }
    if (index == count) {
        add(e);
        return;
    }
    Node* newNode = new Node(e);
    if (index == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    count++;
}

template<class T>
int DLinkedList<T>::size() {
    return count;
}

template<class T>
bool DLinkedList<T>::empty() {
    return count == 0;
}

template<class T>
T DLinkedList<T>::get(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template<class T>
void DLinkedList<T>::set(int index, const T &e) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->data = e;
}

template<class T>
int DLinkedList<T>::indexOf(const T &item) {
    Node* current = head;
    for (int i = 0; i < count; i++) {
        if (current->data == item) {
            return i;
        }
        current = current->next;
    }
    return -1;
}

template<class T>
bool DLinkedList<T>::contains(const T &item) {
    return indexOf(item) != -1;
}