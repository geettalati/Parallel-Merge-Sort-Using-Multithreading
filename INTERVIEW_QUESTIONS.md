# Parallel Merge Sort - Interview Questions & Answers

This document contains a comprehensive list of potential interview questions and answers regarding this Parallel Merge Sort implementation. It covers algorithm concepts, C++ multithreading, system design, and performance optimizations.

## 1. Algorithm & Complexity

**Q: What is the time and space complexity of standard Merge Sort?**
**A:** 
- **Time Complexity:** $O(N \log N)$ in all cases (worst, average, and best). 
- **Space Complexity:** $O(N)$ due to the temporary auxiliary arrays (or vectors) used during the merging phase.

**Q: How does Parallel Merge Sort improve the time complexity?**
**A:** Theoretically, with an infinite number of processors, the time complexity of Parallel Merge Sort is $O(N)$ or $O(\log^2 N)$ depending on how the merge step is parallelized. In this specific implementation, the array division and sub-array sorting are parallelized, but the merge step itself is executed sequentially by the parent thread. Thus, the asymptotic time complexity remains bottlenecked by the merge step. However, the wall-clock execution time is drastically reduced by a factor proportional to the number of available CPU cores because large independent sub-arrays are sorted concurrently.

**Q: What is the `THRESHOLD` constant in your code (set to 5000), and why did you introduce it?**
**A:** The `THRESHOLD` acts as a base-case optimization. Creating, context-switching, and destroying threads has an overhead. If we spawn a new thread for very small sub-arrays (e.g., 10 or 100 elements), the operating system overhead heavily outweighs the benefits of parallel processing. When a sub-array's size falls below the `THRESHOLD`, the algorithm avoids creating new threads and instead falls back to `std::sort` (which typically uses a highly optimized Introsort) to sort the chunk sequentially and rapidly.

## 2. Multithreading & Concurrency in C++

**Q: Your README mentions a "Thread Pool", but your code dynamically spawns new `std::thread` objects for every recursive call. Can you explain this discrepancy?**
**A:** *[Note: Always be honest in interviews if documentation and code drift]* The current `ParallelMergeSort` implementation actually dynamically creates threads on the fly using `std::thread` and waits for them using `.join()`. It does not currently utilize a fixed thread pool. A true thread pool implementation would pre-allocate a fixed number of worker threads (e.g., matching the number of hardware cores) and push sorting tasks to a thread-safe task queue. The dynamic thread creation approach works well for moderate dataset sizes but can cause significant overhead for massive datasets. Implementing a genuine thread pool is the planned next evolution for this project.

**Q: Why do you use `.join()` instead of `.detach()`?**
**A:** We must use `.join()` because the parent thread needs to wait for both child threads to completely finish sorting their respective left and right halves before it can proceed to the `merge` phase. If we used `.detach()`, the parent would immediately attempt to merge data that hasn't been sorted yet, leading to a race condition and invalid output.

**Q: Are there any race conditions in your parallel implementation?**
**A:** No, there are no race conditions during the parallel execution. This is because each spawned thread operates on a strictly disjoint subset of the array indices (defined by `left` to `mid`, and `mid + 1` to `right`). Since no two threads write to or read from the same memory locations concurrently, no mutexes or locks are required during the recursive sorting phase.

## 3. Performance & Scalability

**Q: What would happen if you ran this algorithm on a 100-Million element array using the current implementation?**
**A:** Because we spawn 2 new threads for every split until the chunk size is `< 5000`, for 100 million elements, we would create roughly $100,000,000 / 5000 = 20,000$ leaf nodes. This means tens of thousands of threads would be created overall. This would likely cause thread exhaustion, potentially crash the program with a `std::system_error`, or severely degrade performance due to massive context-switching overhead by the OS scheduler.

**Q: How would you fix the thread exhaustion issue?**
**A:** We can limit the number of active threads by querying the system for available cores using `std::thread::hardware_concurrency()`. If the number of active threads reaches this hardware limit, the algorithm should stop spawning new threads and recursively call the sort function sequentially on the current thread.

**Q: Can the `merge` step itself be parallelized?**
**A:** Yes. Currently, the merge step runs sequentially in $O(N)$ time. To parallelize the merge step, you can find the median of the first array, use binary search to find its proper position in the second array, and recursively spawn threads to merge the left partitions and the right partitions. This brings the overall parallel time complexity closer to $O(\log^2 N)$.

## 4. C++ Language Specifics

**Q: In your code, you capture `[this, left, mid]` in the lambda passed to the thread. Why do you need `this`?**
**A:** `this` is captured so that the lambda inside the newly created thread can call the member function `recursiveSort` and access the member variable `nums` of the `ParallelMergeSort` class instance.

**Q: Why do you dynamically allocate `MergeSort* mergesort = new MergeSort(&nums);` in `main.cpp` instead of using stack allocation?**
**A:** In the `main` function, stack allocation like `MergeSort mergesort(&nums);` would be perfectly fine and actually preferred to avoid manual memory management (`delete mergesort`). Using `new` was a specific design choice, but in modern C++, relying on stack allocation or smart pointers (`std::unique_ptr`) is considered safer to prevent accidental memory leaks.

**Q: How do you prevent out-of-bounds errors when passing the `&nums` pointer to your class?**
**A:** In C++, `std::vector` naturally manages its own bounds. However, we also explicitly check if `(*nums).size() == 0` at the start of the `sort()` function to prevent initiating the recursion on an empty dataset.
