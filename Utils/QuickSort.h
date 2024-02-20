
namespace SORT
{
    template <typename T>
    void  Swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    template <typename T>
    int Partition(T* arr, int low, int high, bool (*compare)( T&,  T&))
    {
        T pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) 
        {
            if (compare(arr[j], pivot)) {
                i++;
                Swap(arr[i], arr[j]);
            }
        }

        Swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    template <typename T>
    void QuickSort(T* arr, int low, int high, bool (*compare)( T&,  T&)) 
    {
        if (low < high) 
        {
            int partitionIndex = Partition(arr, low, high, compare);

            QuickSort(arr, low, partitionIndex - 1, compare);
            QuickSort(arr, partitionIndex + 1, high, compare);
        }
    }


    template <typename T>
    void BubbleSort(T* arr, size_t size, bool (*compare)( T&,  T&))
    {
        for (size_t i = 0; i < size - 1; i++)
        {
            for (size_t j = 0; j < size - i - 1; j++)
            {
                if (compare(arr[j], arr[j + 1]))
                {
                    Swap(arr[j], arr[j + 1]);
                }
            }
        }
    }



}