# ParallelScan
Parallel Merge Sort Implemented via OpenMP
 
### 1. Test Environment
- Hardware
    - AMD Ryzen 5 3500x (6 physical cores, and 6 logical cores)  
    - 16 GB DRAM (3200MHz, 2 slots used - each socket is occupied by a 8 GB DRAM)  
- Software
    - Windows 10  
    - CMake 3.22.1  
    - gcc version 6.3.0 (MinGW.org GCC-6.3.0-1)  
    - GNU Make 3.81   

### 2. How to Build
- Use the CMakeLists.  
    1. mkdir build && cd build  
    2. cmake .. (or cmake .. -G "MinGW Makefiles")  
    3. make  

### 3. Implementation details
- Two pass algorithm
    - Divide   
    - Combine   
