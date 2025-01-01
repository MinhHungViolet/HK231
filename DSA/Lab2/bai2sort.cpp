template <class T>
void Sorting<T>::selectionSort(T *start, T *end)
{
    int length = end - start;
    for(int i = 0; i < length-1; i++){
        int min = start[i];
        int min_index = i;
        for(int j = i+1; j < length; j++){
            if (start[j] < min)  {
                min = start[j];
                min_index = j;
            }            
        }
        swap(start[i], start[min_index]);
        Sorting<T>::printArray(start, end);
    }
}