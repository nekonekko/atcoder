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

const int BIG_NUM = 8 * 1e5;

// from: https://algo-logic.info/segment-tree/
/* SEGTREE: [0,n-1] について、区間ごとの最小/最大値を管理する構造体
    update(a,b,x): 区間[a,b) の要素に x を加算。O(log(n))
    query(a,b): [a,b) での最小/最大の要素を取得。O(log(n))
*/
template <typename T>
struct SEGTREE {
    // const T INF = numeric_limits<T>::max();
    int n;
    bool is_minimum;
    vector<T> dat, lazy;
    SEGTREE(int n_, bool is_minimum_) : n(), is_minimum(is_minimum_), dat(n_ * 4, 0), lazy(n_ * 4, BIG_NUM) {
        int x = 1;
        while (n_ > x) x *= 2;
        n = x;
    }

    /* lazy eval */
    void eval(int k) {
        if (lazy[k] == BIG_NUM) return;  // 更新するものが無ければ終了
        if (k < n - 1) {             // 葉でなければ子に伝搬
            if (lazy[k * 2 + 1] == BIG_NUM) {
                lazy[k * 2 + 1] = lazy[k];
            } else {
                lazy[k * 2 + 1] += lazy[k];
            }
            if (lazy[k * 2 + 2] == BIG_NUM) {
                lazy[k * 2 + 2] = lazy[k];
            } else {
                lazy[k * 2 + 2] += lazy[k];
            }
        }
        // 自身を更新
        dat[k] += lazy[k];
        lazy[k] = BIG_NUM;
    }

    void update(int a, int b, T x, int k, int l, int r) {
        eval(k);
        if (a <= l && r <= b) {  // 完全に内側の時
            lazy[k] = x;
            eval(k);
        } else if (a < r && l < b) {                     // 一部区間が被る時
            update(a, b, x, k * 2 + 1, l, (l + r) / 2);  // 左の子
            update(a, b, x, k * 2 + 2, (l + r) / 2, r);  // 右の子
            if (is_minimum)
                dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
            else
                dat[k] = max(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
    void update(int a, int b, T x) { update(a, b, x, 0, 0, n); }

    T query_sub(int a, int b, int k, int l, int r) {
        eval(k);
        if (r <= a || b <= l) {  // 完全に外側の時
            return BIG_NUM;
        } else if (a <= l && r <= b) {  // 完全に内側の時
            return dat[k];
        } else {  // 一部区間が被る時
            T vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            if (is_minimum)
                return min(vl, vr);
            else
                return max(vl, vr);
        }
    }
    T query(int a, int b) { return query_sub(a, b, 0, 0, n); }

    int find_rightest(int a, int b, T x) { return find_rightest_sub(a, b, x, 0, 0, n); }
    int find_rightest_sub(int a, int b, T x, int k, int l, int r) {
        eval(k);
        if (dat[k] > x || r <= a || b <= l) {  // 自分の値がxより大きい or [a,b)が[l,r)の範囲外ならreturn a-1
            return a - 1;
        } else if (k >= n - 1) {  // 自分が葉ならその位置をreturn
            return k - (n - 1);
        } else {
            int vr = find_rightest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r);
            if (vr != a - 1) {  // 右の部分木を見て a-1 以外ならreturn
                return vr;
            } else {  // 左の部分木を見て値をreturn
                return find_rightest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2);
            }
        }
    }

    /* debug */
    inline T operator[](int a) { return query(a, a + 1); }
    void print() {
        for (int i = 0; i < 2 * n - 1; ++i) {
            cout << (*this)[i];
            if (i != n) cout << ",";
        }
        cout << endl;
    }
};

int main() {
    int N;
    cin >> N;
    vector<int> L(N), R(N);
    for (int i = 0; i < N; i++) {
        cin >> L[i] >> R[i];
    }

    int Q;
    cin >> Q;
    vector<int> X(Q);
    for (int i = 0; i < Q; i++) {
        cin >> X[i];
    }

    SEGTREE<int> min_tree(BIG_NUM, true);


    for (int i = 0; i < min_tree.n; i++) {
        min_tree.dat[min_tree.n - 1 + i] = i + 1;
    }
    for (int i = min_tree.n - 2; i >= 0; i--) {
        min_tree.dat[i] = min(min_tree.dat[i * 2 + 1], min_tree.dat[i * 2 + 2]);
    }

    for (int i = 0; i < N; i++) {
        int new_l, new_r;
        new_l = min_tree.find_rightest(0, min_tree.n - 1, L[i] - 1);
        new_r = min_tree.find_rightest(0, min_tree.n - 1, R[i]);
        min_tree.update(new_l + 1, new_r + 1, 1);
    }

    for (int i = 0; i < min_tree.n * 2 - 1; i++) {
        min_tree.query(i, i + 1);
    }

    for (int i = 0; i < Q; i++) {
        int final_rate;
        final_rate = min_tree.dat[min_tree.n - 2 + X[i]];
        cout << final_rate << endl;
    }
}
