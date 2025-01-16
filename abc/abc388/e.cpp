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

    int left = -1;
    int right = N / 2;
    int mid;
    while (left + 1 < right) {
        mid = (left + right) / 2;
        bool ok = true;
        // cout << left << " " << right << " " << mid << endl;
        for (int i = 0; i < mid; ++i) {
            if (2 * A[i] > A[N - mid + i]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            left = mid;
        } else {
            right = mid;
        }
    }
    cout << right << endl;

}
