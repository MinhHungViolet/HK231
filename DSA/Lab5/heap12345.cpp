template<class T>
void Heap<T>::ensureCapacity(int minCapacity) {
    if (minCapacity > capacity) {
        capacity *= 2;
        T* temp = new T[capacity];
        memcpy(temp, elements, count * sizeof(T));
        delete[] elements;
        elements = temp;
    }
}

template<class T>
void Heap<T>::reheapUp(int position) {
    if (position > 0) {
        int parent = (position - 1) / 2;
        if (elements[position] > elements[parent]) {
            swap(elements[position], elements[parent]);
            reheapUp(parent);
        }
    }
}

template<class T>
void Heap<T>::reheapDown(int position) {
    int leftChild = 2 * position + 1;
    int rightChild = 2 * position + 2;
    int largest = position;
    if (leftChild < count && elements[leftChild] > elements[largest])
        largest = leftChild;
    if (rightChild < count && elements[rightChild] > elements[largest])
        largest = rightChild;
    if (largest != position) {
        swap(elements[position], elements[largest]);
        reheapDown(largest);
    }
}

template<class T>
void Heap<T>::push(T item) {
    ensureCapacity(count + 1);
    elements[count] = item;
    reheapUp(count);
    count++;
}

template<class T>
bool Heap<T>::isEmpty() {
    return count == 0;
}

template<class T>
bool Heap<T>::contains(T item) {
    for (int i = 0; i < count; i++) {
        if (elements[i] == item)
            return true;
    }
    return false;
}

template<class T>
T Heap<T>::peek() {
    if (count == 0)
        return -1; // or throw an exception
    return elements[0];
}

template<class T>
bool Heap<T>::pop() {
    if (count == 0)
        return false;
    elements[0] = elements[count - 1];
    count--;
    if (count > 0)
        reheapDown(0);
    return true;
}

template<class T>
int Heap<T>::size() {
    return count;
}
template<class T>
int Heap<T>::getItem(T item) {
    for (int i = 0; i < count; i++) {
        if (elements[i] == item)
            return i;
    }
    return -1;
}

template<class T>
void Heap<T>::remove(T item) {
    int index = getItem(item);
    if (index == -1)
        return;
    elements[index] = elements[count - 1];
    count--;
    reheapDown(index);
    reheapUp(index);
}

template<class T>
void Heap<T>::clear() {
    delete[] elements;
    capacity = 10;
    count = 0;
    elements = new T[capacity];
}
////////////////////////////////
//Helping functions go here
static void heapify(T* start, T* end, int index){
	int size = end - start;
	int largest = index; 
	int l = 2 * index + 1; 
	int r = 2 * index + 2; 

	if (l < size && start[l] > start[largest])
		largest = l;

	if (r < size && start[r] > start[largest])
		largest = r;

	if (largest != index) {
		swap(start[index], start[largest]);
		heapify(start, end, largest);
	}
}

static void heapSort(T* start, T* end){
    // TODO
	int size = end - start;
	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(start, end, i);

	for (int i = size - 1; i > 0; i--) {
		swap(start[0], start[i]);
		heapify(start, start + i, 0);
	}
	Sorting<T>::printArray(start, end);
}
//////////////////////////bai5
class PrinterQueue
{
public:

    string maxHeap[200];
    int size = 0;
    
public:
    PrinterQueue(){
        for(int i = 0 ; i < 200; i++){
            maxHeap[i] = "";
        }
    }



    void addNewRequest(int priority, string fileName)
    {
        if(maxHeap[priority] == "") maxHeap[priority] = fileName;
        else maxHeap[priority] += " " + fileName;
    }

    void print()
    {
        for(int i = 200 - 1 ; i >= 0; i--){
            if(maxHeap[i] != ""){
                int index = maxHeap[i].find(" ");
                if(index == -1){
                    cout << maxHeap[i] << endl;
                    maxHeap[i] = "";
                }
                else{
                    cout << maxHeap[i].substr(0,index) << endl;
                    maxHeap[i] = maxHeap[i].substr(index+1);
                }
                return;
            }
        }
        cout << "No file to print" << endl;
    }

    
};