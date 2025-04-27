#include <any>
#include <cassert>
#include <cctype>
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
    string S;
    cin >> S;
    int Q;
    cin >> Q;
    int N = S.size();
    for (int i = 0; i < Q; ++i) {
        long long K;
        cin >> K;
        char s = S[(K - 1) % N];
        long long n_words = (K + N - 1) / N - 1;
        int cnt = 0;
        while (n_words > 0) {
            if (n_words & 1) {
                cnt += 1;
            }
            n_words >>= 1;
        }
        if (cnt % 2 == 0) {
            cout << s << " ";
        } else {
            cout << (char)(s ^ 0x20) << " ";  // Toggle case
        }
    }
    cout << endl;
    return 0;
}
