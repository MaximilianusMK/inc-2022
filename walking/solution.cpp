#pragma GCC optimize "-O2"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

const int maxn = 100005;
const int maxdepth = 29;

int N;
vector<pii> con[maxn];
vector<int> all_xor;

int cnt = 0;
int trie[2][2000005];
int nums[2000005];

int set_bit(int x, int k) { return x ^ (1 << k); }
bool is_on(int x, int k) { return (x & (1 << k)) != 0; }


void dfs(int node, int parent, int xor_value) {
  all_xor.push_back(xor_value);
  for (auto next : con[node])
    if (next.first != parent)
      dfs(next.first, node, (xor_value ^ next.second));
}

void insert(int curr, int value, int depth) {
  nums[curr] += 1;
  if (depth < 0) return;
  int bit = is_on(value, depth);
  if (trie[bit][curr] == 0)
    trie[bit][curr] = ++cnt;
  insert(trie[bit][curr], value, depth-1);
}

int greedy_max(int curr, int value, int depth, int ans=0) {
  if (depth < 0) return ans;
  int bit = is_on(value, depth);
  int bot = trie[!bit][curr] != 0 ? !bit : bit;
  return greedy_max(trie[bot][curr], value, depth-1, bot == 0 ? ans : set_bit(ans, depth));
}

int greedy_min(int curr, int value, int depth, int diff=0, int ans=0) {
  if (depth < 0) return ans;
  int bit = is_on(value, depth);
  int bot = trie[bit][curr] == 0 or nums[trie[bit][curr]]+diff < 2 ? !bit : bit;
  return greedy_min(trie[bot][curr], value, depth-1, diff+(bit != bot), bot == 0 ? ans : set_bit(ans, depth));
}


int main(int argc, char *argv[]) {
  scanf("%d", &N);
  for (int i = 0; i < N-1; ++i) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    con[u].push_back({v, w});
    con[v].push_back({u, w});
  }

  dfs(1, 1, 0);

  for (auto x : all_xor)
    insert(0, x, maxdepth);

  int ans_max = 0;
  for (auto x : all_xor) {
    int target = greedy_max(0, x, maxdepth);
    ans_max = max(ans_max, x^target);
  }

  int ans_min = 0x7fffffff;
  for (auto x : all_xor) {
    int target = greedy_min(0, x, maxdepth);
    ans_min = min(ans_min, x^target);
  }

  printf("%d %d\n", ans_min, ans_max);

  return 0;
}
