#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <sys/time.h>
#include <omp.h>


#define GET_SEC(start, end) ((end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec)*1e-6)
#define DTYPE double


const int NUM_THREADS = 6;
const size_t N = ((size_t)1)<<4;
timeval start, end;


void merge_sort_sequential(std::vector<DTYPE>* in, std::vector<DTYPE>* out, size_t start, size_t end);
void merge_sort_parallel(std::vector<DTYPE>* in, std::vector<DTYPE>* out, size_t start, size_t end);
void check_result(std::vector<DTYPE>& in, std::vector<DTYPE>& out);
void print_vector(std::vector<DTYPE>& in);

int main(void) {

    /*******************************************
     * Data initialization
     * in : the input sequence.
     * out : the result of parallel algorithm
     * gt : the ground truth, calculated by the get_groundtruth() function
     ********************************************/
    std::cout << "************************************************************************\n";
    std::cout << "Parallel Scan Algorithm Start\n";
    std::cout << "--- The length of sequence is " << N <<"\n";
    std::cout << "--- The total memory size of sequence is " << N*sizeof(DTYPE)/1024.0/1024/1024*3 <<" GB \n";
    std::cout << "************************************************************************\n";
    srand(time(NULL));

    std::vector<DTYPE> in(N); 
    std::vector<DTYPE> out(N); 
    std::vector<DTYPE> gt(N); 
    std::generate(in.begin(), in.end(), [](){return ((double)(std::rand()%100000-50000))/10000.0f;});

    /*******************************************
     * C++ std::sort 
     ********************************************/
    std::cout << "\nC++ std Sorting Algorithm\n";
    std::copy(in.begin(), in.end(), out.begin());
    gettimeofday(&start, NULL);
    std::sort(out.begin(), out.end());
    gettimeofday(&end, NULL);
    std::copy(out.begin(), out.end(), gt.begin());
    std::cout << "--- Total elapsed time : " << GET_SEC(start, end) << " s\n";


    /*******************************************
     * Sequential Merge Sorting Algorithm
     ********************************************/
    std::cout << "\nSequential Merge Sorting Algorithm\n";
    std::copy(in.begin(), in.end(), out.begin());
    gettimeofday(&start, NULL);
    merge_sort_sequential(&in, &out, 0, in.size()-1);
    gettimeofday(&end, NULL);
    std::cout << "--- Total elapsed time : " << GET_SEC(start, end) << " s\n";
    check_result(gt, out);


    /*******************************************
     * Parallel Merge Sorting Algorithm
     ********************************************/
    std::cout << "\nParallel Merge Sorting Algorithm\n";
    std::copy(in.begin(), in.end(), out.begin());
    gettimeofday(&start, NULL);
    merge_sort_parallel(&in, &out, 0, in.size()-1);
    gettimeofday(&end, NULL);
    std::cout << "--- Total elapsed time : " << GET_SEC(start, end) << " s\n";
    check_result(gt, out);


    return 0;

}


void merge_sort_sequential(std::vector<DTYPE>* in, std::vector<DTYPE>* out, size_t start, size_t end) {

    // Base case
    if (end<=start+1) {
        if ((*in)[end] < (*in)[start]) {
            (*out)[end] = (*in)[start];
            (*out)[start] = (*in)[end];
        }
        return;
    }


    // Divide
    size_t mid = (start+end)/2;
    merge_sort_sequential(in, out, start, mid);
    merge_sort_sequential(in, out, mid+1, end);


    // Conbine
    size_t flag = start;
    size_t flag_left = start;
    size_t flag_right = mid+1;

    while (flag_left <= mid || flag_right <= end) {
        if ((*out)[flag_left] < (*out)[flag_right]) 
            (*in)[flag++] = (*out)[flag_left++];
        else
            (*in)[flag++] = (*out)[flag_right++];
    }

    for (size_t i=flag_left; i<=mid; i++)
        (*in)[flag++] = (*out)[flag_left];

    for (size_t i=flag_right; i<=end; i++)
        (*in)[flag++] = (*out)[flag_right];

    for (size_t i=start; i<=end; i++)
        (*out)[i] = (*in)[i];

}

void merge_sort_parallel(std::vector<DTYPE>* in, std::vector<DTYPE>* out, size_t start, size_t end) {


    // Divide



    // Conbine


}

void check_result(std::vector<DTYPE>& gt, std::vector<DTYPE>& out) {

    std::cout << "--- Start Checking result...\n";
    bool result = true;
    for (size_t i=0; i<gt.size(); i++) {
        if (gt[i] != out[i]) {
            result = false;
            std::cout << "--- [[ERR]] Incorrect at out["<<i<<"] with result="<<out[i]<<" but, gt="<<gt[i]<<"\n";
            break;
        }
    }

    if (result) {
        std::cout << "--- The result is correct!!!\n";
    } else {
        std::cout << "--- The result is incorect!!!\n";
    }

}

void print_vector(std::vector<DTYPE>& in) {
    for(auto i=in.begin(); i!=in.end(); i++)
        std::cout << *i << " ";
    std::cout << std::endl;
}
