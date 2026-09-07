/*
    Given an array containing 0 1 and 2
    We need to sort the array in a single O(N) TC approach without using any extra space
*/

#include <iostream>
#include <utility>

void sort_array(int* &arr, const size_t size) {
    int zero_index = 0;
    int two_index = size-1;

    while (zero_index < size and arr[zero_index] == 0)
        zero_index++;

    while (two_index >= 0 and arr[two_index] == 2)
        two_index--;

    if (zero_index == size or two_index < 0)
        return;

    int index = zero_index;

    while (index < size) {
        if (index > two_index)
            break;

        if (arr[index] == 1)
            index++;

        else if (arr[index] == 0) {
            std::swap(arr[index], arr[zero_index]);
            zero_index++;

            // take me with you, unless i'll keep sitting here and my value would never change
            if (zero_index > index)
                index = zero_index;
        }

        else {
            std::swap(arr[index], arr[two_index]);
            two_index--;
        }
    }

    return;

}

int main() {
    size_t size;
    std::cout << "\nEnter the size of the array : ";
    std::cin >> size;

    int* arr = new int[size];
    std::cout << "\nKeep entering the elements : ";
    for (size_t i=0; i<size; i++)
        std::cin >> arr[i];

    sort_array(arr, size);
    for (size_t i=0; i<size; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n\n";
    
    return 0;
}