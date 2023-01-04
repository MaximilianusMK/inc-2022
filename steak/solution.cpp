#include <bits/stdc++.h>
using namespace std;

int main() {
  int K;
  scanf("%d", &K);

  vector<int> T(K - 1);
  vector<int> A(K);
  vector<int> B(K);

  for (int i = 0; i < K - 1; ++i) {
    scanf("%d", &T[i]);
  }
  for (int i = 0; i < K; ++i) {
    scanf("%d", &A[i]);
  }
  for (int i = 0; i < K; ++i) {
    scanf("%d", &B[i]);
  }

  long long answer = 0;
  int cur_level = K - 1;
  long long cook_time = 0;
  for (int i = K - 1; i >= 0; --i) {
    if (cur_level == i) {
      --cur_level;
      if (cur_level >= 0) {
        cook_time += T[cur_level];
      }
    }
    B[i] -= A[i];
    while (B[i] > 0 && cur_level >= 0) {
      int take = min(A[cur_level], B[i]);
      A[cur_level] -= take;
      B[i] -= take;
      answer += cook_time * take;
      if (A[cur_level] == 0) {
        --cur_level;
        if (cur_level >= 0) {
          cook_time += T[cur_level];
        }
      }
    }
    if (B[i] > 0) {
      puts("-1");
      return 0;
    }
    if (i > 0) {
      cook_time -= T[i - 1];
    }
  }
  printf("%lld\n", answer);
}
