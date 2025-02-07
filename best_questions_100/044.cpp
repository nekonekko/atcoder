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
    vector<int> tetrahedron;
    long long n = 1;
    while (true) {
        long long current = n * (n + 1) * (n + 2) / 6;
        if (current >= 1e6) {
            break;
        }
        tetrahedron.push_back(current);
        n++;
    }

    int sz = tetrahedron.size();
    vector<int> dp(1e6 + 1, 1e9);
    vector<int> dp_odd(1e6 + 1, 1e9);
    dp[0] = 0;
    dp_odd[0] = 0;
    for (int i = 0; i <= sz; i++) {
        for (int j = 0; j < 1e6; j++) {
            if (tetrahedron[i] + j >= 1e6) {
                break;
            }
            if (dp[j] != -1) {
                dp[tetrahedron[i] + j] = min(dp[tetrahedron[i] + j], dp[j] + 1);
            }
            if (dp_odd[j] != -1 && tetrahedron[i] % 2 == 1) {
                dp_odd[tetrahedron[i] + j] =
                    min(dp_odd[tetrahedron[i] + j], dp_odd[j] + 1);
            }
        }
    }

    while (true) {
        int N;
        cin >> N;
        if (N == 0) {
            break;
        }
        cout << dp[N] << " " << dp_odd[N] << endl;
    }
    return 0;
}
