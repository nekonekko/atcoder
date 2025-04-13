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
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(2 * N);
        for (int i = 0; i < 2 * N; ++i) {
            cin >> A[i];
            A[i]--;
        }

        vector<bool> already_togather(N, false);
        for (int i = 0; i < 2 * N - 1; ++i) {
            int a = A[i];
            int b = A[i + 1];
            if (a == b) {
                already_togather[a] = true;
            }
        }

        vector<pair<int, int>> pos(N, {-1, -1});
        for (int i = 0; i < 2 * N; ++i) {
            if (already_togather[A[i]]) continue;
            if (pos[A[i]].first == -1) {
                pos[A[i]].first = i;
            } else {
                pos[A[i]].second = i;
            }
        }

        int ans = 0;
        set<pair<int, int>> s;
        for (int i = 0; i < 2 * N - 1; ++i) {
            if (already_togather[A[i]] || already_togather[A[i + 1]]) continue;

            int a = A[i];
            int b = A[i + 1];
            if (a > b) swap(a, b);

            if (s.count({a, b})) continue;

            int a1 = pos[a].first;
            int a2 = pos[a].second;
            int b1 = pos[b].first;
            int b2 = pos[b].second;
            vector<int> v = {a1, a2, b1, b2};
            sort(v.begin(), v.end());
            if (v[0] == v[1] - 1 && v[2] == v[3] - 1) {
                ans++;
                s.insert({a, b});
            }
        }
        cout << ans << endl;
    }
    return 0;
}
