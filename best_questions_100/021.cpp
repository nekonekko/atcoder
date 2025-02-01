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
    cin >> N;
    vector<long long> H(N), S(N);
    for (int i = 0; i < N; i++) {
        cin >> H[i] >> S[i];
    }

    long long left = 0;
    long long right = 1e18;
    while (right - left > 1) {
        long long mid = (left + right) / 2;
        vector<int> time_limit(N, 0);
        bool ok = true;
        for (int i = 0; i < N; i++) {
            if (mid < H[i]) {
                ok = false;
                break;
            }
            long long time = (mid - H[i]) / S[i];
            if (time >= N) {
                time = N - 1;
            }
            time_limit[int(time)]++;
        }
        if (!ok) {
            left = mid;
            continue;
        }

        for (int i = 0; i < N; i++) {
            if (time_limit[i] > i + 1) {
                ok = false;
                break;
            }
            time_limit[i + 1] += time_limit[i];
        }
        if (ok) {
            right = mid;
        } else {
            left = mid;
        }
    }
    cout << right << endl;

    return 0;
}
