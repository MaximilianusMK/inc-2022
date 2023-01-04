#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

// inputs
int R, C;
vector<string> strings;

const int K = 18;
vector<vector<int>> sparse;
pair<pair<int,int>,int> pn[(1 << K) + 5], tmp[(1 << K) + 5];
int psum[(1 << K) + 5];
vector<vector<int>> subrank;
vector<vector<int>> inv_subrank;

// Counting sort for pn
void countingSort(int n, int class_size) {
  // sort 2nd
  for(int i = 0;i <= class_size;i++) psum[i] = 0;
  for(int i = 0;i < n;i++) {
    psum[pn[i].first.second]++;
  }
  for(int i = 1;i < class_size;i++) psum[i] += psum[i - 1];
  for(int i = n - 1;i >= 0;i--) {
    int idx = --psum[pn[i].first.second];
    tmp[idx] = pn[i];
  }

  // sort 1st
  for(int i = 0;i <= class_size;i++) psum[i] = 0;
  for(int i = 0;i < n;i++) {
    psum[tmp[i].first.first]++;
  }
  for(int i = 1;i <= class_size;i++) psum[i] += psum[i - 1];
  for(int i = n - 1;i >= 0;i--) {
    int idx = --psum[tmp[i].first.first];
    pn[idx] = tmp[i];
  }
}

void buildSA() {
  int class_size = max(27, C + 1);
  sparse.push_back({});
  for(int i = 0;i < R;i++) {
    for(int j = 0;j < C;j++) {
      sparse[0].push_back(strings[i][j] - 'a' + 1);
    }
    sparse[0].push_back(0);
  }

  int n = sparse[0].size();

  // build initial pn (for n = 1)
  for(int j = 0;j < n;j++) {
    pn[j].first.first = pn[j].first.second = sparse[0][j];
    pn[j].second = j;
  }
  countingSort(n, class_size);
  sparse[0][pn[0].second] = 0;
  class_size = 1;
  for(int j = 1;j < n;j++) {
    if(pn[j - 1].first != pn[j].first) class_size++;
    sparse[0][pn[j].second] = class_size - 1;
  }

  int iter = 0;
  while((1 << iter) < n) iter++;

  for(int i = 1; i <= iter;i++) {
    sparse.push_back(vector<int>(n, 0));

    int add = (1 << (i - 1));
    for(int j = 0;j < n;j++) {
      pn[j].first.first = sparse[i - 1][j];
      pn[j].first.second = 0;
      if(j + add < n) {
        pn[j].first.second = sparse[i - 1][j + add];
      }
      pn[j].second = j;
    }

    countingSort(n, class_size);

    sparse[i][pn[0].second] = 0;
    class_size = 1;
    for(int j = 1;j < n;j++) {
      if(pn[j - 1].first != pn[j].first) class_size++;
      sparse[i][pn[j].second] = class_size - 1;
    }
  }
}

// Build rank for each column
void buildSubRank() {
  subrank.resize(C + 1, vector<int>(R, 0));
  inv_subrank.resize(C + 1, vector<int>(0));

  int n = sparse[0].size();
  for(int i = 0;i < n;i++) {
    int r = pn[i].second / (C + 1);
    int c = pn[i].second % (C + 1);
    subrank[c][r] = inv_subrank[c].size();
    inv_subrank[c].push_back(r);
  }
}

struct node {
  int total;
  node *left, *right;
};

node *head[(1 << K) + 5];

node *update(node *prev, int l, int r, int target) {
  node *cur = new node(); // can speed up by avoiding the dynamic allocation
  cur->left = prev->left;
  cur->right = prev->right;
  cur->total = prev->total + 1;
  if(l == r) return cur;
  int mid = (l + r) / 2;
  if(target <= mid) cur->left = update(prev->left, l, mid, target);
  else cur->right = update(prev->right, mid + 1, r, target);
  return cur;
}

int query(node *cur, int l, int r, int le, int ri) {
  if(r < le || ri < l) return 0;
  if(le <= l && r <= ri) {
    return cur->total;
  }
  int mid = (l + r) / 2;
  return query(cur->left, l, mid, le, ri)
    + query(cur->right, mid + 1, r, le, ri);
}

void buildPersistent() {
  head[0] = new node(); /// for self loop, to avoid accessing nullptr
  head[0]->total = 0;
  head[0]->left = head[0]->right = head[0];

  int n = sparse[0].size();
  // we use the last information from pn for ordering
  for(int i = 0;i < n;i++) {
    int idx = pn[i].second;
    int row = idx / (C + 1);
    int col = idx % (C + 1);

    int new_idx = col * R + row;
    head[i + 1] = update(head[i], 0, n, new_idx); // don't forget about this offset
  }
}

void processStrings() {
  cin >> R >> C;
  for(int i = 0;i < R;i++) {
    string s;
    cin >> s;
    strings.push_back(s);
  }

  buildSA();
  buildSubRank();
  buildPersistent();
}

int getLargestNotEqual(int row, int l_char, int r_char, int h, pair<int,int> &cur) {
  int lo = 0;
  int hi = subrank[l_char][row];

  int inv = inv_subrank[l_char][0];
  int result = sparse[sparse.size() - 1][inv * (C + 1) + l_char] - 1;
  while(lo <= hi) {
    int mid = (lo + hi) / 2;

    int inv = inv_subrank[l_char][mid];
    int l_sa_idx = inv * (C + 1) + l_char;
    int r_sa_idx = inv * (C + 1) + r_char - (1 << h) + 1;
    pair<int,int> tar = {sparse[h][l_sa_idx], sparse[h][r_sa_idx]};

    if(cur != tar) {
      result = sparse[sparse.size() - 1][l_sa_idx];
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  return result + 1; // need to offset by 1, we use 0 for self loop in persistent
}

int getLargestEqual(int row, int l_char, int r_char, int h, pair<int,int> &cur) {
  int lo = subrank[l_char][row];
  int hi = subrank[l_char].size() - 1;
  int result = sparse[sparse.size() - 1][row * (C + 1) + l_char];
  while(lo <= hi) {
    int mid = (lo + hi) / 2;

    int inv = inv_subrank[l_char][mid];
    int l_sa_idx = inv * (C + 1) + l_char;
    int r_sa_idx = inv * (C + 1) + r_char - (1 << h) + 1;
    pair<int,int> tar = {sparse[h][l_sa_idx], sparse[h][r_sa_idx]};

    if(cur == tar) {
      result = sparse[sparse.size() - 1][l_sa_idx];
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  return result + 1; // need to offset by 1, we use 0 for self loop in persistent
}

pair<int,int> getPersistentHeadIdx(int row, int l_char, int r_char) {
  int l_sa_idx = row * (C + 1) + l_char;

  int length = r_char - l_char + 1;
  int h = 0;
  while((1 << h) <= length) h++; // can precompute this to optimize
  h--;

  int r_sa_idx = row * (C + 1) + r_char - (1 << h) + 1;
  pair<int,int> cur = {sparse[h][l_sa_idx], sparse[h][r_sa_idx]};

  return {getLargestNotEqual(row, l_char, r_char, h, cur),
      getLargestEqual(row, l_char, r_char, h, cur)};
}

void processQueries() {
  int Q;
  cin >> Q;
  int n = sparse[0].size();
  for(int i = 0;i < Q;i++) {
    int a, b, l, r, x;
    cin >> a >> b >> l >> r >> x;
    a--, b--, l--, r--, x--;

    int real_row = a + x;

    pair<int,int> h = getPersistentHeadIdx(real_row, l, r);
    int not_same = query(head[h.first], 0, n, l * R + a, l * R + b);
    int same = query(head[h.second], 0, n, l * R + a, l * R + real_row)
    - query(head[h.first], 0, n, l * R + a, l * R + real_row); // need to exclude, already computed in 'not_same'.

    cout << same + not_same << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  processStrings();
  processQueries();
}
