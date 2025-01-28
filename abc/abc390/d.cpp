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

unordered_set<long long> st;

void dfs(int idx, int group_num, vector<long long> &A, vector<long long> &sum) {
    // cout << "idx: " << idx << " group_num: " << group_num << endl;
    if (idx == A.size()) {
        long long res = 0;
        // for (int i = 1; i <= group_num; i++) {
        //     cout << sum[i] << " ";
        // }
        // cout << endl;
        for (int i = 1; i <= group_num; i++) {
            res ^= sum[i];
        }
        st.insert(res);
        return;
    }

    for (int i = 1; i <= group_num; i++) {
        sum[i] += A[idx];
        dfs(idx + 1, group_num, A, sum);
        sum[i] -= A[idx];
    }
    if (group_num < A.size()) {
        sum[group_num + 1] = A[idx];
        dfs(idx + 1, group_num + 1, A, sum);
    }
}

int main() {
    int N;
    cin >> N;
    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    vector<long long> sum(N + 1, 0);
    dfs(0, 0, A, sum);

    cout << st.size() << endl;

    return 0;
}
