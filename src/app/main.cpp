#include <iostream>
#include <cstdlib>
#include <chrono>
#include "sorting/mergeSort.hpp"

int main(int argc, char *argv[]) {
    const int SIZE = 10;
    std::vector<int> nums(SIZE);
    for (int i = 0; i < SIZE; i++) {
        nums[i] = rand() % 10; // Fill with random numbers
    }

    MergeSort* mergesort = new MergeSort(&nums);
    auto start = std::chrono::high_resolution_clock::now();
    mergesort->sort();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> mergesortDuration = end - start;
    std::cout << "Merge Sort took " << mergesortDuration.count() << " seconds." << std::endl;

    delete mergesort;
    return 0;
}