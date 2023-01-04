#pragma GCC optimize "-O2"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int N, M;
int A[MAXN];

int main(int argc, char *argv[]) {
  scanf("%d %d", &N, &M);
  for (int i = 1; i <= N; ++i) {
    scanf("%d", &A[i]);
  }

  int ans_ngood = 0, ans_rating = 0;

  for (int i = 1; i <= N; ++i) {
    for (int j = i+1; j <= N; ++j) {
      for (int k = j+1; k <= N; ++k) {
        int hi = max(A[i], max(A[j], A[k]));
        int lo = min(A[i], min(A[j], A[k]));
        int delta = hi - lo;
        int sigma = A[i] + A[j] + A[k];
        if (delta <= M) {
          ans_ngood += 1;
          ans_rating = max(ans_rating, sigma);
        }
      }
    }
  }

  if (ans_ngood == 0)
    printf("-1\n");
  else
    printf("%d %d\n", ans_ngood, ans_rating);
  
  return 0;
}
