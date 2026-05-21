# Parallel Merge Sort Implementation

![C++](https://img.shields.io/badge/C++-11%2B-blue.svg)
![Multithreading](https://img.shields.io/badge/Concurrency-Multithreading-brightgreen.svg)
![Performance](https://img.shields.io/badge/Performance-Optimized-success.svg)

## Overview

This project presents an implementation of the Merge Sort algorithm utilizing parallel processing in C++. By leveraging multithreading, the sorting process is significantly accelerated, especially for large datasets. The implementation demonstrates the use of thread pools and efficient synchronization mechanisms to achieve optimal performance.

## Features

- **Parallel Processing**: Utilizes multiple CPU threads to perform sorting concurrently, reducing execution time.
- **Thread Pool**: Manages a pool of threads to handle sorting tasks efficiently.
- **Performance Benchmarking**: Compares execution times between standard Merge Sort and Parallel Merge Sort, highlighting the performance gains achieved through parallelism.

## Implementation Details

The implementation focuses on enhancing the traditional Merge Sort algorithm by introducing parallelism. The key components include:

- **Recursive Division**: The dataset is recursively divided into smaller subarrays until a threshold is reached.
- **Parallel Sorting**: Subarrays are sorted in parallel using multiple threads.
- **Merging**: Sorted subarrays are merged to produce the final sorted array.

### Thread Pool

A thread pool is employed to manage the creation and synchronization of threads efficiently. This approach minimizes the overhead associated with frequent thread creation and destruction, leading to better resource utilization and performance.

## Performance Comparison

Benchmark tests were conducted to compare the execution times of the standard Merge Sort and the Parallel Merge Sort implementations. On my father's MacBook M1, the standard Merge Sort executed in approximately 25 seconds, while the Parallel Merge Sort completed the same task in about 1 second, demonstrating a significant performance improvement.

## Getting Started

### Prerequisites

- **C++ Compiler**: Ensure you have a C++ compiler that supports C++11 or later.
- **CMake**: Used for building the project.

### Installation

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/geettalati/Parallel-Merge-Sort-Using-Multithreading.git
   cd "Parallel-Merge-Sort-Using-Multithreading"/src/app
   g++ main.cpp -o main -pthread
   ./main
   ```

## Core Concepts Demonstrated

This project showcases a deep understanding of core computer science and software engineering principles:
- **Multithreading & Concurrency**: Effective thread management, synchronization, and parallel execution across CPU cores.
- **Algorithm Optimization**: Taking a standard $O(N \log N)$ algorithm and significantly optimizing its wall-clock execution time by distributing work.
- **Systems-Level Programming**: Managing system resources and threads natively using modern C++.
- **Performance Profiling**: Empirically measuring and proving theoretical improvements through benchmarking.

## Future Enhancements

- **Dynamic Thread Allocation**: Dynamically scale the number of threads based on hardware concurrency limits at runtime (`std::thread::hardware_concurrency()`).
- **Hybrid Sorting Approach**: Implement Insertion Sort for very small sub-arrays at the bottom of the recursion tree to reduce overhead.
- **Generic Templating**: Refactor the algorithm using C++ templates to support sorting of any comparable data types.
