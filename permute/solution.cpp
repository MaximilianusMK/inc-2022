#include <bits/stdc++.h>

int main() {
  int N;
  scanf("%d", &N);
  std::vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
    --A[i];
    if (A[i] < 0) {
      A[i] = N;
    }
  }

  std::vector<std::vector<int>> adj(N);
  std::vector<int> degree(N);
  std::stack<int> stack;
  stack.push(N);
  for (int i = N - 1; i >= 0; --i) {
    int lastPop = -1;
    while (stack.top() < A[i]) {
      lastPop = stack.top();
      stack.pop();
    }

    if (stack.top() != A[i]) {
      return 0 * printf("-1\n");
    }

    if (lastPop >= 0) {
      adj[lastPop].push_back(i);
      ++degree[i];
    }
    if (stack.top() < N) {
      adj[i].push_back(stack.top());
      ++degree[stack.top()];
    }
    stack.push(i);
  }

  std::queue<int> q;
  for (int i = 0; i < N; ++i) {
    if (degree[i] == 0) {
      q.push(i);
    }
  }

  std::vector<int> ans(N);
  for (int i = 0; i < N; ++i) {
    ans[q.front()] = i;
    for (int j : adj[q.front()]) {
      if (--degree[j] == 0) {
        q.push(j);
      }
    }
    q.pop();
  }

  for (int i = 0; i < N; ++i) {
    printf("%d%c", ans[i] + 1, " \n"[i + 1 == N]);
  }
  return 0;
}
