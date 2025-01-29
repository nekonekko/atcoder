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

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    int Q;
    cin >> Q;
    vector<int> M(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> M[i];
    }

    set<int> sums;
    sums.insert(0);
    for (int i = 0; i < N; i++) {
        set<int> add_sums;
        for (auto s: sums) {
            add_sums.insert(s + A[i]);
        }
        sums.insert(add_sums.begin(), add_sums.end());
    }

    for (int i = 0; i < Q; i++) {
        if (sums.count(M[i])) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }

    return 0;
}
