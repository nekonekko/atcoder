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

int solve(int num, int N, int X, int sum, int count) {
    if (count == 3) {
        if (sum == X) {
            return 1;
        } else {
            return 0;
        }
    }
    int res = 0;
    for (int i = num + 1; i <= N; i++) {
        res += solve(i, N, X, sum + i, count + 1);
    }
    return res;
}

int main() {
    while (true) {
        int N, X;
        cin >> N >> X;
        if (N == 0 && X == 0) {
            break;
        }
        cout << solve(0, N, X, 0, 0) << endl;
    }

}
