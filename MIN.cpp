#include <iostream>
#include <climits>
#include <cstdlib>
#include <chrono>
#include <omp.h>

using namespace std;


int findMinSequential(int arr[], int n) {
    int min_value = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }
    return min_value;
}    
int findMinParallel(int arr[], int n) {
    int min_value = INT_MAX;
#pragma omp parallel for reduction(min: min_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }
    return min_value;
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
    cout << "Sequential Min = " << findMinSequential(arr, n) << endl;
    auto endSeq = chrono::steady_clock::now();
     chrono::duration<double, micro> sqMin = endSeq - startSeq;
    cout << "Sequential Elapsed time for Min in microseconds: " << sqMin.count() << " microsecs" << endl;
    
    auto startParallel = chrono::steady_clock::now();
    cout << "Parallel Min = " << findMinParallel(arr, n) << endl;
    auto endParallel = chrono::steady_clock::now();
      chrono::duration<double, micro> parrMin = endParallel - startParallel;
    cout << "Parallel Elapsed time for Min in microseconds: " << parrMin.count() << " microsecs" << endl;
double MinSpeedup = sqMin.count() / parrMin.count();
    cout << "Speedup Min: " << MinSpeedup << endl;
    
    delete[] arr; // Don't forget to release the allocated memory
    return 0;
}

