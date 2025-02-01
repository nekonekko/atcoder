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
    int D, N, M;
    cin >> D >> N >> M;
    vector<int> shop(N + 1);
    shop[0] = 0;
    for (int i = 1; i < N; i++) {
        cin >> shop[i];
    }
    shop[N] = D;
    vector<int> customer(M);
    for (int i = 0; i < M; i++) {
        cin >> customer[i];
    }

    sort(shop.begin(), shop.end());

    int ans = 0;
    for (int i = 0; i < M; i++) {
        int dist;
        auto it = lower_bound(shop.begin(), shop.end(), customer[i]);
        dist = *it - customer[i];
        if (it != shop.begin()) {
            dist = min(dist, customer[i] - *(--it));
        }
        ans += dist;
    }
    cout << ans << endl;
    return 0;
}
