#include <iostream>
#include <vector>
using namespace std;


int knapsack(int W, vector<int>& weights, vector<int>& values, int n) {

    // create a DP table to store the maximum value at each capacity
    // n+1 rows, W+1 columns and all initialized to 0
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // build the DP table
    for (int i = 1; i <= n; i++) {  // loop over each item
        for (int w = 0; w <= W; w++) {  // loop over each capacity from 0 to N
            if (weights[i - 1] <= w) {
                // take the maximum of including the item or not including it
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                // if the item's weight exceeds the capacity, we don't include it
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    // the value in dp[n][W] is the maximum value for the given weight W and n items
    return dp[n][W];
}

int main() {
    int n; // number of items
    int W; // capacity of knapsack

    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> weights(n);
    vector<int> values(n);

    cout << "Enter the weights of the items: ";
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    cout << "Enter the values of the items: ";
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    cout << "Enter the capacity of the knapsack: ";
    cin >> W;

    int maxValue = knapsack(W, weights, values, n);
    cout << "The maximum value that can be obtained is: " << maxValue << endl;

    return 0;
}
