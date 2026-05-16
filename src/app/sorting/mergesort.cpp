#include "mergeSort.hpp"

MergeSort::MergeSort(std::vector<int> *nums) {
    this->nums = nums;
}

MergeSort::~MergeSort() {
    // No dynamic memory to free
}

void MergeSort::recursiveSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        recursiveSort(left, mid);
        recursiveSort(mid + 1, right);
        // Merge the two sorted halves

        std::vector<int> result;
        int i = left, j = mid + 1;
        while (i <= mid && j <= right) {
            if ((*nums)[i] < (*nums)[j]) {
                result.push_back((*nums)[i]);
                i++;
            } else {
                result.push_back((*nums)[j]);
                j++;
            }
        } 

        while(i <= mid) {
            result.push_back((*nums)[i]);
            i++;
        }
        
        while(j <= right) {
            result.push_back((*nums)[j]);
            j++;
        }
        for (int k = left; k <= right; k++) {
            (*nums)[k] = result[k - left];
        }
        
    }
    return;
}

void MergeSort::sort() {
    if (nums->empty()) return;
    recursiveSort(0, nums->size() - 1);
} 