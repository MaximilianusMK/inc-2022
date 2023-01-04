#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

void ac() {
  std::cout << "AC\n";
  exit(0);
}

void wa(std::string reason="") {
  std::cout << "WA\n";
  if (reason != "") {
    std::cout << reason << '\n';
  }
  exit(0);
}

int readInt(std::ifstream &ifs) {
  int ret;
  if (!(ifs >> ret)) wa();
  return ret;
}

bool eof(std::ifstream &ifs) {
  std::string dummy;
  if (ifs >> dummy) return false;
  return true;
}

bool isPermutation(std::vector<int> P) {
  std::sort(P.begin(), P.end());
  for (int i = 0; i < P.size(); ++i) {
    if (P[i] != i) return false;
  }
  return true;
}

std::vector<int> getNearest(std::vector<int> P) {
  std::stack<int> s;
  std::vector<int> ret(P.size(), -1);
  for (int i = P.size() - 1; i >= 0; --i) {
    while (!s.empty() && P[s.top()] < P[i]) {
      s.pop();
    }
    if (!s.empty()) ret[i] = s.top();
    s.push(i);
  }
  return ret;
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Must be run with arguments [input-file] [output-file] [contestant-output]\n";
    exit(0);
  }

  std::ifstream inp(argv[1]);
  std::ifstream out(argv[2]);
  std::ifstream con(argv[3]);

  int N = readInt(inp);
  int judgeAns = readInt(out);

  std::vector<int> P(N);
  P[0] = readInt(con);

  if (judgeAns == -1) {
    if (P[0] != -1) wa();
    if (!eof(con)) wa();
    ac();
  }

  for (int i = 1; i < N; ++i) P[i] = readInt(con);
  if (!eof(con)) wa();

  for (int i = 0; i < N; ++i) --P[i];
  if (!isPermutation(P)) wa();

  for (int num : getNearest(P)) {
    if (num >= 0) ++num;
    if (num != readInt(inp)) wa();
  }
  ac();
}
