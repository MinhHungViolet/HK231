template <class T>
class SLinkedList
{
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration
protected:
    Node *head;
    Node *tail;
    int count;
public:
    SLinkedList() : head(NULL), tail(NULL), count(0){};
    ~SLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    T removeAt(int index);
    bool removeItem(const T &removeItem);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    string toString();
    SLinkedList(const SLinkedList &list)
    {
        this->count = 0;
        this->head = NULL;
        this->tail = NULL;
    }
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }
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
            next = 0;
        }
        Node(Node *next)
        {
            this->next = next;
        }
        Node(T data, Node *next = NULL)
        {
            this->data = data;
            this->next = next;
        }
    };
    class Iterator
    {
    private:
        SLinkedList<T> *pList;
        Node *current;
        int index; 
    public:
        Iterator(SLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        
        Iterator &operator++();
        
        Iterator operator++(int);
    };
};
template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin) {
    this->pList = pList;
    if (begin) {
        if (pList != nullptr) {
            current = pList->head;
            index = 0;
        } else {
            current = nullptr;
            index = -1;
        }
    } else {
        if (pList != nullptr) {
            current = nullptr;
            index = pList->count;
        } else {
            current = nullptr;
            index = 0;
        }
    }
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator) {
    this->pList = iterator.pList;
    this->current = iterator.current;
    this->index = iterator.index;
    return *this;
}

template <class T>
void SLinkedList<T>::Iterator::remove() {
    if (current == nullptr) {
        throw std::out_of_range("Segmentation fault!");
    }
    if (pList->head == current) {
        pList->removeAt(0);
        current = pList->head;
        index = 0;
    } else {
        Node* prev = pList->head;
        while (prev->next != current) {
            prev = prev->next;
        }
        prev->next = current->next;
        Node* temp = current;
        current = prev->next;
        delete temp;
        index--;
    }
}

template <class T>
void SLinkedList<T>::Iterator::set(const T& e) {
    if (current == nullptr) {
        throw std::out_of_range("Segmentation fault!");
    }
    current->data = e;
}

template <class T>
T& SLinkedList<T>::Iterator::operator*() {
    if (current == nullptr) {
        throw std::out_of_range("Segmentation fault!");
    }
    return current->data;
}

template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator) {
    return current != iterator.current || index != iterator.index;
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++() {
    if (current == nullptr) {
        throw std::out_of_range("Segmentation fault!");
    }
    if (current == pList->tail) {
        current = nullptr;
        index = pList->count;
    } else {
        current = current->next;
        index++;
    }
    return *this;
}

template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int) {
    Iterator iterator = *this;
    ++*this;
    return iterator;
}