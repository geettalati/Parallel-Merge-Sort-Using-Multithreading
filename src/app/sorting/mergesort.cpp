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
    }
}

void MergeSort::sort() {
    if (nums->empty()) return;
    recursiveSort(0, nums->size() - 1);
} 