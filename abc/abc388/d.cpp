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

    vector<int> minus_list(N);
    vector<int> plus_list(N);
    for (int i = 0; i < N; ++i) {
        minus_list[i] = N - i - 1;
        plus_list[i] = i;
    }

    priority_queue<int, vector<int>, greater<int> > can_distribute_idx;
    for (int i = 0; i < N; ++i) {
        A[i] += can_distribute_idx.size();

        minus_list[i] = min(minus_list[i], A[i]);
        A[i] -= minus_list[i];
        // cout << "i: " << i << " minus_list[i]: " << minus_list[i] << " A[i]: " << A[i] << " size: " << can_distribute_idx.size() << endl;
        can_distribute_idx.push(i + minus_list[i]);
        while (true) {
            if (can_distribute_idx.empty() || can_distribute_idx.top() > i) {
                break;
            }
            can_distribute_idx.pop();
        }
    }

    for (int i = 0; i < N; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}
