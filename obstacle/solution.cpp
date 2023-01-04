#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100000;
int A[N + 5];

int main() {
  int n;
  cin >> n;
  for(int i = 1;i <= n;i++) cin >> A[i];

  int previous = 0;
  int length = 1;
  int result = min(2, n);

  for(int i = 3;i <= n;i += 2) {
    int diff = A[i] - A[i - 2];
    int has_next = 1;
    if(i == n) {
      has_next = 0;
    }
    if(diff == -2 || diff == 0 || diff == 2) {
      length += 2;
    } else {
      length = 1;
      previous = 1;
    }
    result = max(result, previous + length + has_next);
  }

  cout << result << endl;
}
