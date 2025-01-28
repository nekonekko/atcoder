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
    int N, X;
    cin >> N >> X;
    vector<long long> A1, A2, A3;
    vector<int> C1, C2, C3;
    for (int i = 0; i < N; i++) {
        int v_type, c;
        long long a;
        cin >> v_type >> a >> c;
        if (v_type == 1) {
            A1.push_back(a);
            C1.push_back(c);
        } else if (v_type == 2) {
            A2.push_back(a);
            C2.push_back(c);
        } else {
            A3.push_back(a);
            C3.push_back(c);
        }
    }

    // dp[i][j]: i番目までの食べ物でjカロリーまで摂取したときの最大ビタミン量
    vector<vector<long long>> dp1(A1.size() + 1, vector<long long>(X + 1, 0));
    vector<vector<long long>> dp2(A2.size() + 1, vector<long long>(X + 1, 0));
    vector<vector<long long>> dp3(A3.size() + 1, vector<long long>(X + 1, 0));

    for (int i = 0; i < A1.size(); i++) {
        for (int j = 0; j <= X; j++) {
            if (j - C1[i] >= 0) {
                dp1[i + 1][j] = max(dp1[i + 1][j], dp1[i][j - C1[i]] + A1[i]);
            }
            dp1[i + 1][j] = max(dp1[i + 1][j], dp1[i][j]);
        }
    }
    for (int i = 0; i < A2.size(); i++) {
        for (int j = 0; j <= X; j++) {
            if (j - C2[i] >= 0) {
                dp2[i + 1][j] = max(dp2[i + 1][j], dp2[i][j - C2[i]] + A2[i]);
            }
            dp2[i + 1][j] = max(dp2[i + 1][j], dp2[i][j]);
        }
    }
    for (int i = 0; i < A3.size(); i++) {
        for (int j = 0; j <= X; j++) {
            if (j - C3[i] >= 0) {
                dp3[i + 1][j] = max(dp3[i + 1][j], dp3[i][j - C3[i]] + A3[i]);
            }
            dp3[i + 1][j] = max(dp3[i + 1][j], dp3[i][j]);
        }
    }

    for (int j = 1; j <= X; j++) {
        dp1[A1.size()][j] = max(dp1[A1.size()][j], dp1[A1.size()][j - 1]);
    }
    for (int j = 1; j <= X; j++) {
        dp2[A2.size()][j] = max(dp2[A2.size()][j], dp2[A2.size()][j - 1]);
    }
    for (int j = 1; j <= X; j++) {
        dp3[A3.size()][j] = max(dp3[A3.size()][j], dp3[A3.size()][j - 1]);
    }

    long long ans = 0;
    for (int X1 = 0; X1 <= X; X1++) {
        for (int X2 = 0; X2 <= X - X1; X2++) {
            int X3 = X - X1 - X2;
            long long minimum_vitamin = min({dp1[A1.size()][X1], dp2[A2.size()][X2], dp3[A3.size()][X3]});
            ans = max(ans, minimum_vitamin);
        }
    }

    cout << ans << endl;

    return 0;
}
