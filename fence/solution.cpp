#include <cstring>
#include <iostream>
using namespace std;

const int N = 500;
int dp[N * N];

int arr[N + 1];

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    int total   = 0;
    int exclude = -1;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        if (arr[i] == 2) exclude = i;
        total += arr[i];
    }

    if (total & 1) {
        cout << "NO" << endl;
        return 0;
    }

    if (exclude != -1) total -= 2;
    int length = total / 2;

    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        if (i == exclude) continue;
        for (int j = length; j >= arr[i]; j--) {
            if (dp[j - arr[i]]) dp[j] = 1;
        }
    }

    if (dp[length] || (length >= 1 && dp[length - 1] && exclude != -1)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}
