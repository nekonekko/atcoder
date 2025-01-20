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

const int INF = 3 * 1000000; // 3 * 10^6

int main() {
    int N;
    cin >> N;

    vector<vector<int>> G(N);

    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    vector<int> deg(N);
    for (int i = 0; i < N; i++) {
        deg[i] = G[i].size();
    }

    int ans = INF;
    for (int root = 0; root < N; root++) {
        vector<int> deg_list(deg[root]);
        for (int i = 0; i < deg[root]; i++) {
            deg_list[i] = deg[G[root][i]] - 1;
            // cout << G[root][i] << " " << deg[G[root][i]] << endl;
        }
        sort(deg_list.rbegin(), deg_list.rend());
        for (int x = 1; x <= deg[root]; x++) {
            int y = deg_list[x - 1];
            int need_to_del = N - 1 - x - (x * y);
            ans = min(ans, need_to_del);
            // cout << "root: " <<  root << " " << x << " " << y << " " << need_to_del << endl;
        }
    }

    cout << ans << endl;

    return 0;
}


