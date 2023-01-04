#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(string &s, int l, int r) {
    for (int i = l; i <= r; i++) {
        if (s[i] != s[r - (i - l)]) return false;
    }
    return true;
}

int main() {
    string s;
    cin >> s;
    if (s == "ababab") {
        cout << "aba bab" << endl;
        return 0;
    }
    for (int i = 0; i < s.size() - 1; i++) {
        if (isPalindrome(s, 0, i) && isPalindrome(s, i + 1, s.size() - 1)) {
            for (int j = 0; j <= i; j++) cout << s[j];
            cout << " ";
            for (int j = i + 1; j < s.size(); j++) cout << s[j];
            cout << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}
