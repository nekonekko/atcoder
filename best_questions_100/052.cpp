#include <any>
#include <cassert>
#include <cfenv>
#include <cfloat>
#include <charconv>
#include <cinttypes>
#include <ciso646>
#include <clocale>
#include <codecvt>
#include <condition_variable>
#include <csetjmp>
#include <csignal>
#include <cstdbool>
#include <ctgmath>
#include <forward_list>
#include <fstream>
#include <future>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <regex>
#include <scoped_allocator>
#include <set>
#include <shared_mutex>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <variant>

using namespace std;

int move_nui_num(int S, vector<vector<int>> &cum, int nui) {
    // S: すでに並び替え済みのぬいの種類
    // cum[i][j]: i番目までの棚に、ぬい j が何個あるか
    // nui: 次に揃えるぬい
    int start_idx = 0;
    int N = cum.size() - 1;
    int M = cum[0].size();
    for (int i = 0; i < M; i++) {
        if (S & (1 << i)) {
            start_idx += cum[N][i];
        }
    }
    int end_idx = start_idx + cum[N][nui];
    int nui_between = cum[end_idx][nui] - cum[start_idx][nui];
    return cum[N][nui] - nui_between;
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        A[i]--;
    }
    // cum[i][j] = i番目までの棚に、ぬい j が何個あるか
    // i: 1-indexed, j: 0-indexed
    vector<vector<int>> cum(N + 1, vector<int>(M, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cum[i + 1][j] = cum[i][j];
        }
        cum[i + 1][A[i]]++;
    }

    // dp[i][S] = 左から i 番目のぬいの種類まで決めたときに、
    // 決定済みのぬいの種類が S である時の最小コスト
    vector<vector<int>> dp(M, vector<int>(1 << M, 1e9));
    // 初期化。一番左のぬいの種類を決める
    for (int i = 0; i < M; i++) {
        dp[0][1 << i] = move_nui_num(0, cum, i);
    }

    for (int i = 1; i < M; i++) {
        for (int S = 0; S < (1 << M); S++) {
            if (dp[i - 1][S] == 1e9) {
                continue;
            }
            for (int j = 0; j < M; j++) {
                if (S & (1 << j)) {
                    continue;
                }
                int T = S | (1 << j);
                dp[i][T] =
                    min(dp[i][T], dp[i - 1][S] + move_nui_num(S, cum, j));
            }
        }
    }

    cout << dp[M - 1][(1 << M) - 1] << endl;

    return 0;
}
