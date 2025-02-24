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
    int V, E;
    cin >> V >> E;
    vector<vector<long long>> G(V, vector<long long>(V, 1e18));
    for (int i = 0; i < V; i++) {
        G[i][i] = 0;
    }
    for (int i = 0; i < E; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        G[s][t] = d;
    }
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (G[i][k] == 1e18 || G[k][j] == 1e18) {
                    continue;
                }
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if (G[i][i] < 0) {
            cout << "NEGATIVE CYCLE" << endl;
            return 0;
        }
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << (G[i][j] == 1e18 ? "INF" : to_string(G[i][j]));
            if (j < V - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
