#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;

int N, Q;
bool T[MAXN+5];
long long diff[MAXN+5];
long long ans;
map<int,int> ranges;

void off(int idx) {
  if (ranges.count(idx)) {
    int r = ranges[idx];
    ranges.erase(idx);
    ans -= diff[r-idx+1];

    if (idx != r) {
      ranges[idx+1] = r;
      ans += diff[r-idx];
    }
    return;
  }
  auto it = ranges.lower_bound(idx);
  it--;

  int l = it->first;
  int r = it->second;
  ans -= diff[r-l+1];
  ranges.erase(l);

  ranges[l] = idx-1;
  ans += diff[idx-l];

  if (idx+1 <= r) {
    ranges[idx+1] = r;
    ans += diff[r-idx];
  }
  return;
}

void on(int idx) {
  if (ranges.empty()) {
    ranges[idx] = idx;
    ans += diff[1];
    return;
  }

  int nextl, nextr, l, r;
  nextl = nextr = l = r = -1;
  auto it = ranges.lower_bound(idx);

  if (it != ranges.end()) {
    nextl = it->first;
    nextr = it->second;
  }
  if (it != ranges.begin()) {
    it--;
    l = it->first;
    r = it->second;
  }

  if (nextl != -1 && l != -1 && r == idx-1 && idx+1 == nextl) {
    ranges.erase(l);
    ans -= diff[r-l+1];

    ranges.erase(nextl);
    ans -= diff[nextr-nextl+1];

    ranges[l] = nextr;
    ans += diff[nextr-l+1];
    return;
  }

  if (nextl != -1 && nextl == idx+1) {
    ranges.erase(nextl);
    ans -= diff[nextr-nextl+1];

    ranges[idx] = nextr;
    ans += diff[nextr-idx+1];
    return;
  }

  if (l != -1 && r == idx-1) {
    ranges.erase(l);
    ans -= diff[r-l+1];

    ranges[l] = idx;
    ans += diff[idx-l+1];
    return;
  }

  ranges[idx] = idx;
  ans += diff[1];
}

int main() {
  cin >> N >> Q;
  for (int i = 1; i <= N; i++) {
    diff[i] = i*(i+1ll)*(i+2ll)/6ll;
  }
  ranges[1] = N;
  ans = diff[N];
  memset(T, true, sizeof T);
  while (Q--) {
    int x;
    cin >> x;
    if (T[x]) off(x);
    else on(x);
    T[x] = !T[x];
    cout << ans << endl;
  }
}
