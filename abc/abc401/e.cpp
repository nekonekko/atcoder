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
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(N);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        G[a - 1].push_back(b - 1);
        G[b - 1].push_back(a - 1);
    }

    vector<bool> already_merged(N, false);
    vector<bool> is_neighbor(N, false);
    already_merged[0] = true;
    set<int> from_zero;
    from_zero.insert(0);
    set<int> neighbors;
    for (int u : G[0]) {
        neighbors.insert(u);
        is_neighbor[u] = true;
    }
    cout << neighbors.size() << endl;

    for (int i = 1; i < N; ++i) {
        if (is_neighbor[i]) {
            queue<int> q;
            q.push(i);
            vector<bool> visited(N, false);
            visited[i] = true;

            while (!q.empty()) {
                int v = q.front();
                q.pop();
                if (!already_merged[v]) {
                    already_merged[v] = true;
                    from_zero.insert(v);
                }
                if (is_neighbor[v]) {
                    neighbors.erase(v);
                    is_neighbor[v] = false;
                }

                for (int u : G[v]) {
                    if (!already_merged[u]) {
                        if (u <= i && !visited[u]) {
                            visited[u] = true;
                            q.push(u);
                        }
                        if (!is_neighbor[u]) {
                            neighbors.insert(u);
                            is_neighbor[u] = true;
                        }
                    }
                }
            }
        }

        if ((int)from_zero.size() == i + 1) {
            cout << neighbors.size() << endl;
        } else {
            cout << -1 << endl;
        }
    }

    return 0;
}
