# ParallelScan
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

### 2. How to Build
- Use the CMakeLists.  
    1. mkdir build && cd build  
    2. cmake .. (or cmake .. -G "MinGW Makefiles")  
    3. make  

### 3. Implementation details
- Two pass algorithm
    - Divide   
    - Combine   
