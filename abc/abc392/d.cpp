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
#include <limits>
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
    vector<int> K(N);
    vector<map<int, int>> A(N);
    for (int i = 0; i < N; i++) {
        cin >> K[i];
        for (int j = 0; j < K[i]; j++) {
            int a;
            cin >> a;
            A[i][a]++;
        }
    }
    long double ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            auto aj = A[j].begin();
            long long current_pair = 0;
            for (auto ai : A[i]) {
                while (aj->first < ai.first) {
                    if (aj == A[j].end()) {
                        break;
                    }
                    aj++;
                }
                if (aj == A[j].end()) {
                    break;
                }
                if (ai.first == aj->first) {
                    current_pair +=
                        (long long)ai.second * (long long)aj->second;
                }
            }
            long double current_ans =
                (long double)current_pair /
                (long double)((long long)(K[i]) * (long long)(K[j]));
            ans = max(ans, current_ans);
        }
    }
    cout << fixed << setprecision(20) << ans << endl;

    return 0;
}
