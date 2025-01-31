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

long long factorial(int n) {
    double res = 1;
    for (int i = 1; i <= n; i++) {
        res *= i;
    }
    return res;
}

int main() {
    int N;
    cin >> N;
    vector<int> X(N), Y(N), idx(N);
    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
        idx[i] = i;
    }

    double sum = 0;
    do {
        double d = 0;
        for (int i = 1; i < N; i++) {
            d +=
                sqrt((X[idx[i]] - X[idx[i - 1]]) * (X[idx[i]] - X[idx[i - 1]]) +
                     (Y[idx[i]] - Y[idx[i - 1]]) * (Y[idx[i]] - Y[idx[i - 1]]));
        }
        sum += d;
    } while (next_permutation(idx.begin(), idx.end()));
    sum /= factorial(N);
    cout << fixed << setprecision(15) << sum << endl;

    return 0;
}
