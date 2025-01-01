template<class T>
void ArrayList<T>::ensureCapacity(int cap){
    if (cap == capacity) {
        int newCapacity = capacity * 1.5;
        T* newData = new T[newCapacity];
        for (int i = 0; i < count; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
}

template <class T>
void ArrayList<T>::add(T e) {
    ensureCapacity(count);
    data[count++] = e;
}

template<class T>
void ArrayList<T>::add(int index, T e) {
    if (index < 0 || index > count) {
        throw std::out_of_range("the input index is out of range!");
    }
    ensureCapacity(count);
    for (int i = count; i > index; i--) {
        data[i] = data[i-1];
    }
    data[index] = e;
    count++;
}

template<class T>
int ArrayList<T>::size() {
    return count;
}