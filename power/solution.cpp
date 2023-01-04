#include <bits/stdc++.h>
using namespace std;

const int MAXX = 2e5+100;

int q;
int cnt[MAXX+10];
int zero;

void update(int idx, int val) {
  if (cnt[idx] == 0 && cnt[idx]+val != 0) {
    zero--;
  }
  else if (cnt[idx] != 0 && cnt[idx]+val == 0) {
    zero++;
  }
  cnt[idx] += val;
}

int main() {
  cin >> q;
  memset(cnt, 0, sizeof cnt);
  zero = MAXX;
  while (q--) {
    char t;
    int x;
    cin >> t >> x;
    int sign = (t == '+') ? 1 : -1;

    update(x, sign);
    while (cnt[x] == 2*sign) {
      update(x, -2*sign);
      x++;
      update(x, sign);
    }

    if (zero == MAXX) cout << "YES" << endl;
    else cout << "NO" << endl;
  }
}
