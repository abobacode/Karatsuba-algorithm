#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

string additional(string s1, string s2) {
    if (s1.empty()) {
        return s2;
    } else if (s2.empty()) {
        return s1;
    }
    string response;
    if (s1.size() < s2.size()) {
        string buffer = s1;
        s1 = s2;
        s2 = buffer;
    }
    int buffer = 0;
    int diff = s1.size() - s2.size();
    for (int i = s1.size() - 1; i >= 0; --i) {
        if (i + s2.size() >= s1.size()) {
            buffer += static_cast <int> (s1[i] - '0') + static_cast <int> (s2[i - diff] - '0');
            response += static_cast <char> (buffer % 10 + '0');
            buffer /= 10;
        } else {
            buffer += static_cast <int> (s1[i] - '0');
            response += static_cast <char> (buffer % 10 + '0');
            buffer /= 10;
        }
    }
    if (buffer != 0) {
        response += static_cast <char> (buffer % 10 + '0');
    }
    reverse(response.begin(), response.end());
    return response;
}

string subtraction(string s1, string s2) {
    if (s2.empty()) {
        return s1;
    }
    if (s1.empty()) {
        return "";
    }
    if (s1.size() > s2.size()) {
        s2 = string(s1.size() - s2.size(), '0') + s2;
    }
    string response;
    for (int i = 0; i < s1.size(); i++) {
        response += ' ';
    }
    int n1, n2;
    int buffer = 0;
    for (int i = response.size() - 1; i >= 0; --i) {
        n1 = s1[i] - '0' - buffer;
        n2 = s2[i] - '0';
        if (n1 >= n2) {
            response[i] = static_cast <char> (n1 - n2 + '0');
            buffer = 0;
        } else {
            response[i] = static_cast <char> (n1 - n2 + 10 + '0');
            buffer = 1;
        }
    }
    bool meet_only_zeros = true;
    string final_response;
    for (int i = 0; i < response.size(); ++i) {
        if (response[i] != '0') {
            meet_only_zeros = false;
        }
        if (!meet_only_zeros) {
            final_response += response[i];
        }
    }
    return final_response;
}

string multiplication(string s1, string s2) {
    if (s1.empty() || s2.empty()) {
        return "";
    }
    if (s1 == "0" || s2 == "0") {
        return "0";
    }
    if (s1.size() <= 64 && s2.size() <= 64) {
        vector <int> ans(s1.size() + s2.size(), 0);
        for (int i = 0; i < s1.size(); ++i) {
            for (size_t j = 0; j < s2.size(); ++j) {
                ans[ans.size() - i - j - 2] +=
                    static_cast <int> (s1[i] - '0') * static_cast <int> (s2[j] - '0');
            }
        }
        for (int i = 0; i < ans.size() - 1; ++i) {
            if (ans[i] > 9) {
                ans[i + 1] += ans[i] / 10;
                ans[i] %= 10;
            }
        }
        string response;
        if (ans[ans.size() - 1] != 0) {
            response += static_cast <char> (ans[ans.size() - 1] + '0');
        }
        for (int i = ans.size() - 2; i >= 0; --i) {
            response += static_cast <char> (ans[i] + '0');
        }
        return response;
    } else {
        if (s1.size() < s2.size()) {
            string buffer = s1;
            s1 = s2;
            s2 = buffer;
        }
        string a, b, c, d;
        bool b_only_zeros = true;
        bool c_only_zeros = true;
        bool d_only_zeros = true;
        for (int i = 0; i < s1.size() / 2; ++i) {
            a += s1[i];
        }
        for (int i = s1.size() / 2; i < s1.size(); ++i) {
            if (s1[i] == '0' && b_only_zeros) {
                continue;
            }
            b += s1[i];
            b_only_zeros = false;
        }
        if (s2.size() <= (s1.size() + 1) / 2) {
            d = s2;
            d_only_zeros = false;
        } else {
            for (int i = 0; i < s2.size() - (s1.size() + 1) / 2; ++i) {
                c += s2[i];
            }
            c_only_zeros = false;
            for (int i = s2.size() - (s1.size() + 1) / 2; i < s2.size(); ++i) {
                if (s2[i] == '0' && d_only_zeros) {
                    continue;
                }
                d += s2[i];
                d_only_zeros = false;
            }
        }
        if (b_only_zeros) {
            b = "";
        }
        if (c_only_zeros) {
            c = "";
        }
        if (d_only_zeros) {
            d = "";
        }
        string ac = multiplication(a, c);
        string bd = multiplication(b, d);
        string ad_plus_bc =
            subtraction(subtraction(multiplication(additional(a, b), additional(c, d)), ac), bd);

        string response;
        if (!ac.empty()) {
            response = ac.append((s1.size() + 1) / 2 * 2, '0');
        }
        if (!ad_plus_bc.empty()) {
            response = additional(response, ad_plus_bc.append((s1.size() + 1) / 2, '0'));
        }
        response = additional(response, bd);
        return response;
    }
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    cout << multiplication(s1, s2);
    return 0;
}
