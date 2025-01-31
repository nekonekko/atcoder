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

int main() {
    int N, Q;
    cin >> N;
    vector<int> S(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }
    cin >> Q;
    vector<int> T(Q);
    for (int i = 0; i < Q; i++) {
        cin >> T[i];
    }
    sort(T.begin(), T.end());

    int s_idx = 0;
    int ans = 0;
    for (int t_idx = 0; t_idx < Q; t_idx++) {
        while (s_idx < N && S[s_idx] < T[t_idx]) {
            s_idx++;
        }
        if (s_idx < N && S[s_idx] == T[t_idx]) {
            ans++;
        }
    }
    cout << ans << endl;

    return 0;
}
