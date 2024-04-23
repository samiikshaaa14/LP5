#include <iostream>
#include <climits>
#include <cstdlib>
#include <chrono>
#include <omp.h>

using namespace std;


int calculateSumSequential(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}
int calculateSumParallel(int arr[], int n) {
    int sum = 0;
#pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}
int main() {
    int *arr, n;
    cout << "\nEnter total number of elements: ";
    cin >> n;

    int lb = 0;
    int ub = n;
    arr = new int[n];

    for (int i = 0; i < n; i++) {
        arr[i] = (rand() % (ub - lb + 1));
    }

    cout << "Generated array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Sequential version
    auto startSeq = chrono::steady_clock::now();
   startSeq = chrono::steady_clock::now();
    cout << "Sequential Sum = " << calculateSumSequential(arr, n) << endl;
    
  
    
    auto endSeq = chrono::steady_clock::now();
    endSeq = chrono::steady_clock::now();
      chrono::duration<double, micro> sqSum = endSeq - startSeq;
    cout << "Sequential Elapsed time for Sum in microseconds: " <<sqSum.count() << " microsecs" << endl;
    
    auto startParallel = chrono::steady_clock::now();
    startParallel = chrono::steady_clock::now();
  cout << "Parallel Sum = " << calculateSumParallel(arr, n) << endl;
    
     auto endParallel = chrono::steady_clock::now();
    endParallel = chrono::steady_clock::now();
      chrono::duration<double, micro> parrSum = endParallel - startParallel;
    cout << "Parallel Elapsed time for Sum in microseconds: " << parrSum.count() << " microsecs" << endl;
    
 

  double SumSpeedup = sqSum.count() / parrSum.count();
    cout << "Speedup Sum: " << SumSpeedup << endl;

    delete[] arr; // Don't forget to release the allocated memory
    return 0;
}

