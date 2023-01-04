#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5;

int n;
ll d[MAX_N + 1], p0, x;

void solve() {
  scanf("%d %lld %lld", &n, &p0, &x);
  d[0] = 0;
  for (int i = 1; i <= n; i++) scanf("%lld", &d[i]);
  ll sum = 0;
  for (int i = 1; i <= n; i++) sum += d[i];
  ll p = p0, ans = LLONG_MAX;
  for (int i = 0; i <= n; i++) {
    p += d[i];
    if (p < x) continue;
    ans = min(ans, (p - x) % abs(sum) + x);
  }
  if (ans == LLONG_MAX) ans = -1;
  printf("%lld\n", ans);
}

int main() {
  int t = 1;
  // scanf("%d", &t);
  for (int tc = 1; tc <= t; tc++) {
    solve();
  }
  return 0;
}
