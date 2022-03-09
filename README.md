# ParallelMergeSort
Parallel Merge Sort Implemented via OpenMP
 
### 1. Test Environment
- Hardware
    - AMD Ryzen 5 3500x (6 physical cores, and 6 logical cores)  
    - 16 GB DRAM (3200MHz, 2 slots used - each socket is occupied by a 8 GB DRAM)  
- Software
    - Ubuntu 7.5.0-3ubuntu1~18.04
    - CMake 3.22.12 
    - gcc version 7.5.0 (Ubuntu 7.5.0-3ubuntu1~18.04)  
    - GNU Make 4.1  
- Performance Result
    - N=2^29 double-type array
    - std::sort : 169 s
    - Naive sequential merge sort : 179 s
    - OpemMP task based parallel merge sort (with 6 threads) : 49 s
        - Speed up : 3.4x

### 2. How to Build
- Use the CMakeLists.txt  
    1. mkdir build && cd build  
    2. cmake .. (or cmake .. -G "MinGW Makefiles")  
    3. make  

### 3. Implementation details
- Two pass algorithm
    - Divide Path 
        - Recursively divide the current array into two contiguous half-arrays (i.e. left and right)
    - Combine Path
        - Two child-arrays (i.e. left and right) are already sorted
        - Merge two child-arrays into a sorted array 
            - Because each child-array is already sorted, just need to compare the first elements of each array, and push the small one into parent-array. Iterate this process until all the elements in child-arrays are pushed into parent-array.
- Parallel optimization strategy
    - Divide Path 
        - Sorting the child-arrays can be executed independently
        - Two threads take one of the child-arrays and process them parallelly
    - Combine Path
        - Combing two arrays into a single array cannot be processed parallelly 
        - Data parallelism is possible when the task is divided into very fine-grained tasks, but this fine-grained parallelism is somewhat inefficient
- Perforamnce factor (N-length array)
    - Work : O(N*logN)
    - Span : O(logN)
