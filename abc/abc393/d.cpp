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

int main() {
    int N;
    cin >> N;
    string S;
    cin >> S;

    vector<int> zero_idx;
    for (int i = 0; i < N; i++) {
        if (S[i] == '0') {
            zero_idx.push_back(i);
        }
    }
    int zero_count = zero_idx.size();

    // debug
    // cout << "zero_idx: ";
    // for (int i = 0; i < zero_count; i++) {
    //     cout << zero_idx[i] << " ";
    // }
    // cout << endl;

    vector<long long> zero_hidariyose_count(zero_count);
    vector<long long> zero_migiyose_count(zero_count);
    for (int i = 0; i < zero_count; i++) {
        zero_hidariyose_count[i] = zero_idx[i] - i;
        zero_migiyose_count[i] = (N - 1) - zero_idx[i] - (zero_count - i - 1);
    }

    // debug
    // for (int i = 0; i < zero_count; i++) {
    //     cout << zero_hidariyose_count[i] << " ";
    // }
    // cout << endl;
    // for (int i = 0; i < zero_count; i++) {
    //     cout << zero_migiyose_count[i] << " ";
    // }
    // cout << endl;

    vector<long long> zero_hidariyose_ruiseki(zero_count + 1);
    vector<long long> zero_migiyose_ruiseki(zero_count + 1);
    for (int i = 0; i < zero_count; i++) {
        zero_hidariyose_ruiseki[i + 1] =
            zero_hidariyose_ruiseki[i] + zero_hidariyose_count[i];
        zero_migiyose_ruiseki[zero_count - i - 1] =
            zero_migiyose_ruiseki[zero_count - i] +
            zero_migiyose_count[zero_count - i - 1];
    }

    // debug
    // cout << "ruiseki: " << endl;
    // for (int i = 0; i < zero_count + 1; i++) {
    //     cout << zero_hidariyose_ruiseki[i] << " ";
    // }
    // cout << endl;
    // for (int i = 0; i < zero_count + 1; i++) {
    //     cout << zero_migiyose_ruiseki[i] << " ";
    // }
    // cout << endl;

    long long ans = 1e18;
    for (int k = 0; k <= zero_count; k++) {
        // k 個左寄せ、つまり、0, 1, 2, ..., k - 1 は左寄せ
        // zero_cout - k 個右寄せ、つまり、k, k + 1, ..., zero_count - 1
        // は右寄せ
        long long current_cost =
            zero_hidariyose_ruiseki[k] + zero_migiyose_ruiseki[k];
        ans = min(ans, current_cost);
    }
    cout << ans << endl;

    return 0;
}
