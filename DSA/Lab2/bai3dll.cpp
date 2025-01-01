// bi loi free 2 lan
template <class T>
class DLinkedList<T>::Iterator
{
private:
    DLinkedList<T> *pList;
    Node *current;
    int index; // is the index of current in pList
public:
    Iterator(DLinkedList<T> *pList, bool begin)
    {
        this->pList = pList;
        if (begin)
        {
            current = pList->head;
            index = 0;
        }
        else
        {
            current = NULL;
            index = pList->count;
        }
    }

    Iterator &operator=(const Iterator &iterator)
    {
        this->pList = iterator.pList;
        this->current = iterator.current;
        this->index = iterator.index;
        return *this;
    }

    void set(const T &e)
    {
        if (current != NULL)
        {
            current->data = e;
        }
    }

    T &operator*()
    {
        if (current != NULL)
        {
            return current->data;
        }
        throw "Out of range";
    }

    bool operator!=(const Iterator &iterator)
    {
        return current != iterator.current;
    }

    void remove()
    {
        if (current != NULL)
        {
            Node *temp = current;
            current = current->next;
            pList->removeAt(index);
            delete temp;
        }
    }

    // Prefix ++ overload
    Iterator &operator++()
    {
        if (current != NULL)
        {
            current = current->next;
            index++;
        }
        return *this;
    }

    // Postfix ++ overload
    Iterator operator++(int)
    {
        Iterator iterator = *this;
        ++*this;
        return iterator;
    }
};