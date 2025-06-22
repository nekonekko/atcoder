#include <any>
#include <atcoder/modint>
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
using namespace atcoder;

using mint = modint998244353;

int main() {
    int N;
    cin >> N;
    vector<vector<int>> A(N, vector<int>(6));

    vector<int> s;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 6; j++) {
            int x;
            cin >> x;
            A[i][j] = x;
            s.push_back(x);
        }
    }

    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());

    int k = s.size();
    vector<vector<int>> upd(k);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 6; j++) {
            int x = lower_bound(s.begin(), s.end(), A[i][j]) - s.begin();
            upd[x].push_back(i);
        }
    }

    mint ans = 0;
    vector<int> b(N);
    mint prod = 1;
    int zero_cnt = N;
    for (int i = 0; i < k - 1; i++) {
        for (int j : upd[i]) {
            if (b[j] == 0) {
                zero_cnt--;
            } else {
                prod /= b[j];
            }
            b[j]++;
            prod *= b[j];
        }
        ans -= (zero_cnt ? 0 : prod) * (s[i + 1] - s[i]);
    }
    ans /= mint(6).pow(N);
    ans += s[k - 1];
    cout << ans.val() << endl;

    return 0;
}
