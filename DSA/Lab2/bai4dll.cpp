template <class T>
class SLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList() : head(NULL), tail(NULL), count(0) {};
    ~SLinkedList() {
        clear();
    };
    void    add(const T &e);
    void    add(int index, const T &e);
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index, const T &e);
    int     indexOf(const T &item);
    bool    contains(const T &item); 
    T       removeAt(int index);
    bool    removeItem(const T &item);
    void    clear();
public:
    class Node
    {
    private:
        T data;
        Node *next;
        friend class SLinkedList<T>;

    public:
        Node()
        {
            this->next = NULL;
        }

        Node(const T &data)
        {
            this->data = data;
            this->next = NULL;
        }
    };
};

template<class T>
T SLinkedList<T>::removeAt(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head;
    Node* previous = NULL;
    for (int i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }
    T data = current->data;
    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }
    if (current == tail) {
        tail = previous;
    }
    delete current;
    count--;
    return data;
}

template<class T>
bool SLinkedList<T>::removeItem(const T &item) {
    Node* current = head;
    Node* previous = NULL;
    while (current != NULL) {
        if (current->data == item) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            if (current == tail) {
                tail = previous;
            }
            delete current;
            count--;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

template<class T>
void SLinkedList<T>::clear() {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = NULL;
    tail = NULL;
    count = 0;
}