#include <vector>
#include <cstdint>
#include <queue>

struct Comp {
    bool operator()(const std::pair<int64_t, int64_t> &lhs, const std::pair<int64_t, int64_t> &rhs) {
        return lhs.second > rhs.second;
    }
};


void Dijkstra(int64_t start, std::vector<int> &dist, std::vector<std::vector<int> > &list_adj) {
    std::priority_queue<std::pair<int64_t, int64_t>, std::vector<std::pair<int64_t, int64_t> >, Comp> que;

    dist[start] = 0;

    que.push({start, 0});
    for (; !que.empty();) {
        auto [curr_v, curr_d] = que.top();
        que.pop();

        if (curr_d > dist[curr_v]) {
            continue;
        }

        for (auto [neig, weight]: list_adj[curr_v]) {
            if (dist[neig] > dist[curr_v] + weight) {
                dist[neig] = dist[curr_v] + weight;
                que.push({neig, dist[neig]});
            }
        }
    }
}
