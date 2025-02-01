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
    long double P;
    cin >> P;

    long double left = 0;
    long double right = 1e18;
    while (right - left > 1e-15) {
        long double mid = (left + right) / 2;
        long double f = 1 - P * log(2) / pow(2, mid / 1.5) * 2 / 3;
        if (f < 0) {
            left = mid;
        } else {
            right = mid;
        }
    }
    long double ans = right + P / pow(2, right / 1.5);
    cout << fixed << setprecision(10) << ans << endl;

    return 0;
}
