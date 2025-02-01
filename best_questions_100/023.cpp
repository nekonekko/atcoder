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
    int N;
    long long M;
    cin >> N >> M;
    vector<long long> P(N + 1);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }
    P[N] = 0;
    vector<long long> two_arrow;
    for (int i = 0; i < N + 1; i++) {
        for (int j = i; j < N + 1; j++) {
            two_arrow.push_back(P[i] + P[j]);
        }
    }
    sort(two_arrow.begin(), two_arrow.end());
    two_arrow.erase(unique(two_arrow.begin(), two_arrow.end()),
                    two_arrow.end());

    long long ans = 0;
    for (long long first_two : two_arrow) {
        auto last_two_iter =
            upper_bound(two_arrow.begin(), two_arrow.end(), M - first_two);
        last_two_iter--;
        long long last_two = *last_two_iter;
        if (first_two + last_two > M) {
            continue;
        }
        ans = max(ans, first_two + last_two);
    }
    cout << ans << endl;

    return 0;
}
