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
    int A, B, C, X, Y;
    cin >> A >> B >> C >> X >> Y;

    int ans = 0;
    // ABは0枚
    ans = A * X + B * Y;
    // ABは2*X枚 
    ans = min(ans, C * 2 * X + B * max(0, Y - X));
    // ABは2*Y枚
    ans = min(ans, C * 2 * Y + A * max(0, X - Y));
    cout << ans << endl;

    return 0;
}
