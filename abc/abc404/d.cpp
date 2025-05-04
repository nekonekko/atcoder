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

#define INF 1e18

long long ans = INF;

void dfs(int zoo_idx, int N, int M, vector<long long> &C,
         vector<vector<int>> &zoo_to_animals, long long sum_cost,
         vector<int> &animal_visited_num) {
    if (zoo_idx == N) {
        bool all_visited = true;
        for (int i = 0; i < M; i++) {
            if (animal_visited_num[i] < 2) {
                all_visited = false;
                break;
            }
        }
        if (all_visited) {
            ans = min(ans, sum_cost);
        }
        return;
    }

    dfs(zoo_idx + 1, N, M, C, zoo_to_animals, sum_cost, animal_visited_num);
    for (int i = 0; i < zoo_to_animals[zoo_idx].size(); i++) {
        animal_visited_num[zoo_to_animals[zoo_idx][i]]++;
    }
    dfs(zoo_idx + 1, N, M, C, zoo_to_animals, sum_cost + C[zoo_idx],
        animal_visited_num);
    for (int i = 0; i < zoo_to_animals[zoo_idx].size(); i++) {
        animal_visited_num[zoo_to_animals[zoo_idx][i]]++;
    }
    dfs(zoo_idx + 1, N, M, C, zoo_to_animals, sum_cost + C[zoo_idx] * 2,
        animal_visited_num);
    for (int i = 0; i < zoo_to_animals[zoo_idx].size(); i++) {
        animal_visited_num[zoo_to_animals[zoo_idx][i]] -= 2;
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<long long> C(N);
    for (int i = 0; i < N; i++) {
        cin >> C[i];
    }
    // vector<vector<int>> animals_to_zoo(M);
    // for (int i = 0; i < M; i++) {
    //     int K;
    //     cin >> K;
    //     for (int j = 0; j < K; j++) {
    //         int A;
    //         cin >> A;
    //         A--;
    //         animals_to_zoo[i].push_back(A);
    //     }
    // }
    vector<vector<int>> zoo_to_animals(N);
    for (int i = 0; i < M; i++) {
        int K;
        cin >> K;
        for (int j = 0; j < K; j++) {
            int A;
            cin >> A;
            A--;
            zoo_to_animals[A].push_back(i);
        }
    }

    vector<int> animal_visited_num(M, 0);
    dfs(0, N, M, C, zoo_to_animals, 0, animal_visited_num);

    cout << ans << endl;

    return 0;
}
