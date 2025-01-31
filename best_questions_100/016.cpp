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
    vector<int> P(N), Q(N);
    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> Q[i];
    }
    int a, b;
    int cnt = 1;
    vector<int> R(N);
    for (int i = 0; i < N; i++) {
        R[i] = i + 1;
    }
    do {
        if (R == P) {
            a = cnt;
        }
        if (R == Q) {
            b = cnt;
        }
        cnt++;
    } while (next_permutation(R.begin(), R.end()));

    cout << abs(a - b) << endl;
    return 0;
}
