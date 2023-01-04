#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int SQRT = 500; // if SQRT = 100 should be accepted
const int N = 200000;

int bf_small[SQRT][SQRT];
bool is_missing[N + 5];

void update(int num, bool missing) {
  is_missing[num] = missing;

  for(int i = 1;i < SQRT;i++) {
    bf_small[i][num % i] += ((missing == true)?1:-1);
  }
}

int query(int n, int num, int k) {
  if(k < SQRT) {
    return bf_small[k][num % k];
  } else {
    int total = 0;
    for(int i = num;i <= n; i += k) {
      total += (is_missing[i]?1:0);
    }
    return total;
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int n;
  cin >> n;
  string s;
  cin >> s;
  for(int i = 0;i < n;i++) {
     if(s[i] == '0') update(i + 1, true);
  }

  int q;
  cin >> q;
  while(q--) {
    int type;
    cin >> type;
    if(type == 1) {
      int a;
      cin >> a;
      update(a, false);
    } else if(type == 2) {
      int b;
      cin >> b;
      update(b, true);
    } else {
      int x, k;
      cin >> x >> k;
      cout << query(n, x, k) << endl;
    }
  }
}
