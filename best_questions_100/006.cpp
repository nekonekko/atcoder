#include <cassert>
#include <cfenv>
#include <cfloat>
#include <ciso646>
#include <clocale>
#include <csetjmp>
#include <csignal>
#include <cstdbool>
#include <cinttypes>
#include <charconv>
#include <typeindex>
#include <any>
#include <scoped_allocator>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <valarray>
#include <variant>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <condition_variable>
#include <shared_mutex>
#include <codecvt>
#include <future>
#include <regex>
#include <iostream>
#include <random>
#include <ctgmath>
#include <fstream>

using namespace std;

int main() {
    int N;
    cin >> N;
    string S;
    cin >> S;

    // count[i][j] = i文字目(1-indexed)までの間に、数字jが何回出現したか
    vector<vector<int>> count(N+1, vector<int>(10, 0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 10; ++j) {
            count[i+1][j] = count[i][j];
        }
        count[i+1][S[i]-'0']++;
    }

    vector<int> pattern;
    // i文字目(1-indexed)が真ん中の文字の場合
    for (int i = 2; i <= N - 1; i++) {
        for (int first = 0; first < 10; ++first) {
            for (int second = 0; second < 10; ++second) {
                // 1文字目候補が存在しない場合
                if (count[i-1][first] == 0) continue;
                // 3文字目候補が存在しない場合
                if (count[N][second] - count[i][second] == 0) continue;
                int current_pattern = first * 100 + (S[i-1]-'0') * 10 + second;
                pattern.push_back(current_pattern);
            }
        }
    }

    sort(pattern.begin(), pattern.end());
    pattern.erase(unique(pattern.begin(), pattern.end()), pattern.end());
    cout << pattern.size() << endl;
    return 0;
}
