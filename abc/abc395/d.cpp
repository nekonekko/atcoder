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
    int Q;
    cin >> Q;
    vector<int> hato(N);
    for (int i = 0; i < N; i++) {
        hato[i] = i;
    }
    vector<int> initial_to_current(N);
    vector<int> current_to_initial(N);
    for (int i = 0; i < N; i++) {
        initial_to_current[i] = i;
        current_to_initial[i] = i;
    }
    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            hato[a] = current_to_initial[b];
        } else if (t == 2) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            initial_to_current[current_to_initial[a]] = b;
            initial_to_current[current_to_initial[b]] = a;
            swap(current_to_initial[a], current_to_initial[b]);
        } else if (t == 3) {
            int a;
            cin >> a;
            a--;
            cout << initial_to_current[hato[a]] + 1 << endl;
        }
        // cout << "---" << endl;
        // for (int i = 0; i < N; i++) {
        //     cout << hato[i] << " ";
        // }
        // cout << endl;
        // for (int i = 0; i < N; i++) {
        //     cout << initial_to_current[i] << " ";
        // }
        // cout << endl;
        // for (int i = 0; i < N; i++) {
        //     cout << current_to_initial[i] << " ";
        // }
        // cout << endl;
    }
    return 0;
}
