#include<iostream>
#include<bits/stdc++.h>
using namespace std;
void bubbleSort(int arr[], int n) {
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            } 
        }
    }
}

void swap_para(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_para(int arr[], int n) {
    int i = 0, j = 0;
    int f;

    for (i = 0; i < n - 1; i++) {
        f = i % 2;
        #pragma omp parallel for default(none), shared(arr, f, n)
        for (j = f; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap_para(&arr[j], &arr[j + 1]);
            } 
        }
    }
}
int main() {
    int n;
    cout << "Enter no of elements in array:";
    cin >> n;
    int arr1[n], arr2[n], arr3[n], arr4[n];
    for (int i = 0; i < n; i++) {
        arr1[i] = rand() % n;
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
        arr4[i] = arr1[i];
    }

    auto start2 = chrono::steady_clock::now();
    bubbleSort(arr3, n);
    auto end2 = chrono::steady_clock::now();
    chrono::duration<double, micro> fp2 = end2 - start2;
    cout << "Sequential Bubble Sort Time: " << fp2.count() << " microseconds" << endl;

    auto start3 = chrono::steady_clock::now();
    bubble_para(arr4, n);
    auto end3 = chrono::steady_clock::now();
    chrono::duration<double, micro> fp3 = end3 - start3;
    cout << "Parallel Bubble Sort Time: " << fp3.count() << " microseconds" << endl;
   
        // Calculate speedup for Bubble Sort
    double BSortSpeedup = fp2.count() / fp3.count();
    cout << "Speedup Bubble Sort: " << BSortSpeedup << endl;

}
