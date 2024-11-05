#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// global counters for swaps and comparisons
int swap_count_deterministic = 0;
int comparison_count_deterministic = 0;
int swap_count_randomized = 0;
int comparison_count_randomized = 0;

// function to swap two elements
void swap(int &a, int &b, int &swap_count) {
    int temp = a;
    a = b;
    b = temp;
    swap_count++;
}

// partition function for deterministic quick sort using the first element as pivot
int partition_deterministic(vector<int> &arr, int low, int high) {
    int pivot = arr[low]; // first element as pivot
    int i = low + 1;

    for (int j = low + 1; j <= high; j++) {
        comparison_count_deterministic++;
        if (arr[j] < pivot) {
            swap(arr[i], arr[j], swap_count_deterministic);
            i++;
        }
    }
    swap(arr[low], arr[i - 1], swap_count_deterministic);
    return i - 1;
}

// deterministic quick sort
void quicksort_deterministic(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pi = partition_deterministic(arr, low, high);
        quicksort_deterministic(arr, low, pi - 1);
        quicksort_deterministic(arr, pi + 1, high);
    }
}

// partition function for randomized quick sort
int partition_randomized(vector<int> &arr, int low, int high) {
    int random_index = low + rand() % (high - low + 1);
    swap(arr[low], arr[random_index], swap_count_randomized); // swap random element with first element
    return partition_deterministic(arr, low, high); // reuse deterministic partition with first element as pivot
}

// randomized quick sort
void quicksort_randomized(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pi = partition_randomized(arr, low, high);
        quicksort_randomized(arr, low, pi - 1);
        quicksort_randomized(arr, pi + 1, high);
    }
}

// function to print the array
void printArray(const vector<int> &arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0)); // seed for random number generator

    int n;
    cout << "Enter the number of elements to sort: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // make copies of the original array for each sorting variant
    vector<int> arr_deterministic = arr;
    vector<int> arr_randomized = arr;

    // apply deterministic quick sort
    quicksort_deterministic(arr_deterministic, 0, n - 1);
    cout << "\nSorted array using deterministic quick sort: ";
    printArray(arr_deterministic);
    cout << "No. of comparisons (deterministic): " << comparison_count_deterministic << endl;
    cout << "No. of swaps (deterministic): " << swap_count_deterministic << endl;

    // apply randomized quick sort
    quicksort_randomized(arr_randomized, 0, n - 1);
    cout << "\nSorted array using randomized quick sort: ";
    printArray(arr_randomized);
    cout << "No. of comparisons (randomized): " << comparison_count_randomized << endl;
    cout << "No. of swaps (randomized): " << swap_count_randomized << endl;

    return 0;
}

// Deterministic & Randomized QS Time Complexity
// Best & Avg case: O(nlogn)
// Worst case: O(n^2)

// Randomized QS is considered better because it reduces the likelihood of encountering the worst-case scenario. It is generally more efficient, but it does introduce slight overhead due to random pivot selection.

// // Deterministic & Randomized QS Space Complexity
// Best & Avg case: O(logn)
// Worst case: O(n)
