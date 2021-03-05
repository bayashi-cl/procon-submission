#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using P = pair<ll, ll>;

const ll LINF = 1LL << 60;

struct Edge {
    ll from;
    ll to;
    ll cost;
};
class Dijkstra {
   public:
    int start;
    int n_node;
    vector<ll> cost;
    vector<vector<P>> graph;
    priority_queue<P, vector<P>, greater<P>> que;

    Dijkstra(int n_node, int start) {
        this->n_node = n_node;
        this->start = start;
        que.push(P(0, start));
        cost.resize(n_node, LINF);
        cost[start] = 0;
        graph.resize(n_node);
    }
    void from_matrix(vector<vector<ll>> adj) {}
    void from_list(vector<vector<P>> adj) { graph = adj; }
    void from_edge(vector<Edge> edge, bool directon) {
        for (Edge e : edge) {
            graph[e.from].push_back(P(e.cost, e.to));
            if (!directon) graph[e.to].push_back(P(e.cost, e.from));
        }
    }
    vector<ll> calc() {
        while (!que.empty()) {
            P p = que.top();
            que.pop();
            ll now = p.second;
            if (cost[now] < p.first) continue;
            for (P adj : graph[now]) {
                ll temp_cost = cost[now] + adj.first;
                if (temp_cost < cost[adj.second]) {
                    cost[adj.second] = temp_cost;
                    que.push(P(cost[adj.second], adj.second));
                }
            }
        }
        return cost;
    }
    ll get_cost(int i) { return cost[i]; }
};
int main() {
    int V, E, r;
    cin >> V >> E >> r;
    vector<Edge> edge;
    for (int i = 0; i < E; i++) {
        Edge e;
        cin >> e.from >> e.to >> e.cost;
        edge.push_back(e);
    }
    Dijkstra d(V, r);
    d.from_edge(edge, true);
    vector<ll> cost = d.calc();
    for (auto&& c : cost) {
        if (c == LINF) {
            cout << "INF" << endl;
        } else {
            cout << c << endl;
        }
    }
    return 0;
}

