template <class T>
class SLinkedList {
public:
    class Node;
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList() : head(nullptr), tail(nullptr), count(0) {};
    ~SLinkedList();
    void add(T e);
    void add(int index, T e);
    int size();
public:
    class Node {
    private:
        T data;
        Node* next;
        friend class SLinkedList<T>;
    public:
        Node() {
            next = nullptr;
        }
        Node(Node* next) {
            this->next = next;
        }
        Node(T data, Node* next) {
            this->data = data;
            this->next = next;
        }
    };
};

template <class T>
void SLinkedList<T>::add(const T& e) {
    Node* newNode = new Node(e, nullptr);
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
void SLinkedList<T>::add(int index, const T& e) {
    if (index < 0 || index > count) {
        throw std::out_of_range("Index out of range!");
    }
    if (index == count) {
        add(e);
        return;
    }
    Node* newNode = new Node(e, nullptr);
    if (index == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* prev = head;
        for (int i = 0; i < index - 1; i++) {
            prev = prev->next;
        }
        newNode->next = prev->next;
        prev->next = newNode;
    }
    count++;
}

template<class T>
int SLinkedList<T>::size() {
    return count;
}