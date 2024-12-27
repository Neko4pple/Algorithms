#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1001;
int n, k;
vector<pair<int, int>> adj[MAXN]; // (도시, 가중치)
int subtree_size[MAXN];
bool visited[MAXN];

// 서브트리의 크기를 계산
void dfs(int node) {
    visited[node] = true;
    subtree_size[node] = 1;
    for (auto& edge : adj[node]) {
        int next_node = edge.first;
        if (!visited[next_node]) {
            dfs(next_node);
            subtree_size[node] += subtree_size[next_node];
        }
    }
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    // 루트가 1인 서브트리의 크기를 계산
    memset(visited, false, sizeof(visited));
    dfs(1);

    // 간선 리스트 생성
    vector<pair<int, pair<int, int>>> edges;
    for (int i = 1; i <= n; ++i) {
        for (auto& edge : adj[i]) {
            int v = edge.first, w = edge.second;
            if (i < v) {
                edges.push_back({w, {i, v}});
            }
        }
    }

    // 간선을 가중치 기준으로 정렬
    sort(edges.begin(), edges.end());

    int total_weight = 0;
    for (auto& edge : edges) {
        int w = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        int min_subtree_size = min(subtree_size[u], subtree_size[v]);
        if (min_subtree_size <= k && min_subtree_size <= n - k) {
            total_weight += w;
        }
    }

    cout << total_weight << endl;

    return 0;
}
