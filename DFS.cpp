#include <vector>

void dfs(size_t v, std::vector<size_t> &vis, std::vector<std::vector<size_t> > &g) {
    vis[v] = 1;
    for (auto neig: g[v]) {
        if (!vis[neig]) {
            dfs(neig, vis, g);
        }
    }
}
