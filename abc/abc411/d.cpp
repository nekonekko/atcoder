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
    cin >> N >> Q;

    vector<tuple<int, int, string>> queries(Q);

    for (int i = 0; i < Q; i++) {
        int t, p;
        string s;
        cin >> t >> p;
        if (t == 2) {
            cin >> s;
            reverse(s.begin(), s.end());
        } else {
            s = "";
        }
        queries[i] = make_tuple(t, p, s);
    }

    string ans;
    int idx = 0;
    for (int i = Q - 1; i >= 0; i--) {
        auto [t, p, s] = queries[i];
        if (t == 1) {
            if (idx == p) {
                idx = 0;
            }
        } else if (t == 2) {
            if (idx == p) {
                ans += s;
            }
        } else if (t == 3) {
            if (idx == 0) {
                idx = p;
            }
        }
    }

    reverse(ans.begin(), ans.end());
    cout << ans << endl;

    return 0;
}
