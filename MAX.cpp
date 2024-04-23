#include <iostream>
#include <climits>
#include <cstdlib>
#include <chrono>
#include <omp.h>

using namespace std;


int findMaxSequential(int arr[], int n) {
    int max_value = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    return max_value;
} 
int findMaxParallel(int arr[], int n) {
    int max_value = INT_MIN;
#pragma omp parallel for reduction(max: max_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    return max_value;
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
    cout << "Sequential Max = " << findMaxSequential(arr, n) << endl;
    
    auto endSeq = chrono::steady_clock::now();
    endSeq = chrono::steady_clock::now();
      chrono::duration<double, micro> sqMax = endSeq - startSeq;
    cout << "Sequential Elapsed time for Max in microseconds: " << sqMax.count() << " microsecs" << endl;
   
    auto startParallel = chrono::steady_clock::now();
    startParallel = chrono::steady_clock::now();
    cout << "Parallel Max = " << findMaxParallel(arr, n) << endl;
    
    auto endParallel = chrono::steady_clock::now();
    endParallel = chrono::steady_clock::now();
      chrono::duration<double, micro> parrMax = endParallel - startParallel;
    cout << "Parallel Elapsed time for Max in microseconds: " << parrMax.count() << " microsecs" << endl;

  double MaxSpeedup = sqMax.count() / parrMax.count();
cout << "Speedup Max: " << MaxSpeedup << endl;

    delete[] arr; // Don't forget to release the allocated memory
    return 0;
}

