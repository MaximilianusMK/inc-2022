#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

const string NO_ANS = "NO";

int ac() {
    puts("AC");
    return 0;
}

int wa(string message) {
    fprintf(stderr, "%s\n", message.c_str());
    puts("WA");
    return 0;
}

string toLowerCase(string s) {
    string result = "";
    for (int i = 0; i < s.size(); i++) {
        result += tolower(s[i]);
    }
    return result;
}

vector<string> parseString(string input) {
    vector<string> result;
    stringstream ss(input);
    string dummy;
    while (ss >> dummy) {
        result.push_back(toLowerCase(dummy));
    }
    return result;
}

bool isPalindrome(string &input) {
    int size = input.size();
    for (int i = 0; i < size; i++) {
        if (input[i] != input[size - 1 - i]) return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    ifstream tc_in(argv[1]);
    ifstream tc_out(argv[2]);
    ifstream con_out(argv[3]);

    string tc_ans;
    getline(tc_out, tc_ans);

    string con_ans;
    if (!getline(con_out, con_ans)) {
        return wa("Unexpected EOF");
    }
    if (tc_ans == NO_ANS) {
        if (toLowerCase(con_ans) != toLowerCase(tc_ans)) {
            return wa("Judge answer is `NO`, contestant answer is " + con_ans);
        }
    } else {
        vector<string> con_ans_list = parseString(con_ans);
        if (con_ans_list.size() != 2) {
            return wa("Contestant doesn't give 2 string");
        }

        vector<string> judge_ans_list = parseString(tc_ans);
        if (judge_ans_list[0] + judge_ans_list[1] != con_ans_list[0] + con_ans_list[1]) {
            return wa("Contestant concat result not equal with input");
        }

        if (!isPalindrome(con_ans_list[0]) || !isPalindrome(con_ans_list[1])) {
            return wa("Contestant result is not palindrome");
        }
    }

    string dummy;
    if ((con_out >> dummy)) {
        return wa("Expected EOF.");
    }
    return ac();
}
