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
    string S;
    cin >> S;

    int ans = 0;
    int count = 0;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == 'A' || S[i] == 'C' || S[i] == 'G' || S[i] == 'T') {
            count++;
        } else {
            ans = max(ans, count);
            count = 0;
        }
    }
    ans = max(ans, count);
    cout << ans << endl;
}
