/*
# import numpy as np

def check_valid(s, N):
    if int(s) == 0 or int(s) > N:
        return False
    return True

def base10int(value, base):
    if (int(value / base)):
        return base10int(int(value / base), base) + str(value % base)
    return str(value % base)

def main():
    A = int(input())
    N = int(input())
    ten_kaibun_list = []
    for a in range(1, 10):
        aa = str(a)
        if check_valid(aa, N):
            ten_kaibun_list.append(aa)
        if check_valid(aa + aa, N):
            ten_kaibun_list.append(aa + aa)
        for b in range(10):
            bb = str(b)
            aba = aa + bb + aa
            if check_valid(aba, N):
                ten_kaibun_list.append(aba)
            abba = aa + bb + bb + aa
            if check_valid(abba, N):
                ten_kaibun_list.append(abba)
            for c in range(10):
                cc = str(c)
                abcba = aa + bb + cc + bb + aa
                if check_valid(abcba, N):
                    ten_kaibun_list.append(abcba)
                abccba = aa + bb + cc + cc + bb + aa
                if check_valid(abccba, N):
                    ten_kaibun_list.append(abccba)
                for d in range(10):
                    dd = str(d)
                    abcdcba = aa + bb + cc + dd + cc + bb + aa
                    if check_valid(abcdcba, N):
                        ten_kaibun_list.append(abcdcba)
                    abcddcba = aa + bb + cc + dd + dd + cc + bb + aa
                    if check_valid(abcddcba, N):
                        ten_kaibun_list.append(abcddcba)
                    for e in range(10):
                        ee = str(e)
                        abcdedcba = aa + bb + cc + dd + ee + dd + cc + bb + aa
                        if check_valid(abcdedcba, N):
                            ten_kaibun_list.append(abcdedcba)
                        abcdeedcba = aa + bb + cc + dd + ee + ee + dd + cc + bb
+ aa if check_valid(abcdeedcba, N): ten_kaibun_list.append(abcdeedcba) for f in
range(10): ff = str(f) abcdefedcba = aa + bb + cc + dd + ee + ff + ee + dd + cc
+ bb + aa if check_valid(abcdefedcba, N): ten_kaibun_list.append(abcdefedcba)
                            abcdeffedcba = aa + bb + cc + dd + ee + ff + ff + ee
+ dd + cc + bb + aa if check_valid(abcdeffedcba, N):
                                ten_kaibun_list.append(abcdeffedcba)

    ans = 0
    for ten_kaibun in ten_kaibun_list:
        a_kaibun = base10int(int(ten_kaibun), A)
        a_kaibun_length = len(str(a_kaibun))
        if a_kaibun_length % 2 == 0:
            a_kaibun = str(a_kaibun)
            if a_kaibun[:a_kaibun_length // 2] == a_kaibun[a_kaibun_length //
2:][::-1]: ans += int(ten_kaibun) else: a_kaibun = str(a_kaibun) if
a_kaibun[:a_kaibun_length // 2] == a_kaibun[a_kaibun_length // 2 + 1:][::-1]:
                ans += int(ten_kaibun)
    print(ans)

if __name__ == "__main__":
    main()
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// int を long long に自分で編集して変更

bool check_valid(const string& s, long long N) {
    long long val = stoll(s);
    if (val == 0 || val > N) return false;
    return true;
}

string base10int(long long value, int base) {
    if (value / base != 0) {
        return base10int(value / base, base) + to_string(value % base);
    }
    return to_string(value % base);
}

int main() {
    int A;
    long long N;
    cin >> A >> N;
    vector<string> ten_kaibun_list;

    for (int a = 1; a < 10; a++) {
        string aa = to_string(a);
        if (check_valid(aa, N)) ten_kaibun_list.push_back(aa);
        if (check_valid(aa + aa, N)) ten_kaibun_list.push_back(aa + aa);
        for (int b = 0; b < 10; b++) {
            string bb = to_string(b);
            string aba = aa + bb + aa;
            if (check_valid(aba, N)) ten_kaibun_list.push_back(aba);
            string abba = aa + bb + bb + aa;
            if (check_valid(abba, N)) ten_kaibun_list.push_back(abba);
            for (int c = 0; c < 10; c++) {
                string cc = to_string(c);
                string abcba = aa + bb + cc + bb + aa;
                if (check_valid(abcba, N)) ten_kaibun_list.push_back(abcba);
                string abccba = aa + bb + cc + cc + bb + aa;
                if (check_valid(abccba, N)) ten_kaibun_list.push_back(abccba);
                for (int d = 0; d < 10; d++) {
                    string dd = to_string(d);
                    string abcdcba = aa + bb + cc + dd + cc + bb + aa;
                    if (check_valid(abcdcba, N))
                        ten_kaibun_list.push_back(abcdcba);
                    string abcddcba = aa + bb + cc + dd + dd + cc + bb + aa;
                    if (check_valid(abcddcba, N))
                        ten_kaibun_list.push_back(abcddcba);
                    for (int e = 0; e < 10; e++) {
                        string ee = to_string(e);
                        string abcdedcba =
                            aa + bb + cc + dd + ee + dd + cc + bb + aa;
                        if (check_valid(abcdedcba, N))
                            ten_kaibun_list.push_back(abcdedcba);
                        string abcdeedcba =
                            aa + bb + cc + dd + ee + ee + dd + cc + bb + aa;
                        if (check_valid(abcdeedcba, N))
                            ten_kaibun_list.push_back(abcdeedcba);
                        for (int f = 0; f < 10; f++) {
                            string ff = to_string(f);
                            string abcdefedcba = aa + bb + cc + dd + ee + ff +
                                                 ee + dd + cc + bb + aa;
                            if (check_valid(abcdefedcba, N))
                                ten_kaibun_list.push_back(abcdefedcba);
                            string abcdeffedcba = aa + bb + cc + dd + ee + ff +
                                                  ff + ee + dd + cc + bb + aa;
                            if (check_valid(abcdeffedcba, N))
                                ten_kaibun_list.push_back(abcdeffedcba);
                        }
                    }
                }
            }
        }
    }

    long long ans = 0;
    for (const auto& ten_kaibun : ten_kaibun_list) {
        long long val = stoll(ten_kaibun);
        string a_kaibun = base10int(val, A);
        int len = a_kaibun.size();
        if (len % 2 == 0) {
            if (a_kaibun.substr(0, len / 2) ==
                string(a_kaibun.rbegin(), a_kaibun.rbegin() + len / 2)) {
                ans += val;
            }
        } else {
            if (a_kaibun.substr(0, len / 2) ==
                string(a_kaibun.rbegin(), a_kaibun.rbegin() + len / 2)) {
                ans += val;
            }
        }
    }

    cout << ans << endl;
    return 0;
}
