#include <bits/stdc++.h>
using namespace std;

const long long INF = 2e18;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int N;
  long long P;
  cin >> N >> P;

  long long mins, maks;
  mins = maks = P;

  for (int i = 0; i < N; i++) {
    char T[2];
    long long C[2];
    cin >> T[0] >> C[0] >> T[1] >> C[1];

    long long cur_mins = INF;
    long long cur_maks = -INF;

    for (int j = 0; j < 2; j++) {
      if (T[j] == '+') {
        cur_mins = min(cur_mins, mins+C[j]);
        cur_maks = max(cur_maks, maks+C[j]);
      }
      else {
        cur_mins = min(cur_mins, mins*C[j]);
        cur_mins = min(cur_mins, maks*C[j]);
        cur_maks = max(cur_maks, mins*C[j]);
        cur_maks = max(cur_maks, maks*C[j]);
      }
    }
    mins = cur_mins;
    maks = cur_maks;
  }
  cout << maks << endl;
  return 0;
}
