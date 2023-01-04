#pragma GCC optimize "-O2"
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;

int N;
int A[maxn];

int main(int argc, char *argv[]) {
  scanf("%d", &N);
  for (int i = 0; i < N; ++i)
    scanf("%d", &A[i]);

  int ans = 0;
  for (int i = 0; i < N; ++i)
    if (A[i] < 0) {
      bool found = false;
      for (int j = 0; j < i; ++j)
        if (A[j] == -A[i]) found = true;
      if (!found) ++ans;
    }

  printf("%d\n", ans);
  
  return 0;
}
