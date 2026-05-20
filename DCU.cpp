#include <vector>

struct DSU {
    std::vector<std::vector<int> > dsu;
    std::vector<int> numbers;

    DSU(int n) : dsu(n + 1), numbers(n + 1) {
        dsu[0] = {};
        for (int i = 1; i <= n; ++i) {
            dsu[i] = {i};
            numbers[i] = i;
        }
    }

    int get(int x) {
        return numbers[x];
    }

    bool check(int a, int b) {
        return numbers[a] == numbers[b];
    }

    void concatenate(int a, int b) {
        if (dsu[numbers[a]].size() <= dsu[numbers[b]].size()) {
            int ind = numbers[a];
            while (!dsu[ind].empty()) {
                dsu[numbers[b]].push_back(dsu[ind].back());
                numbers[dsu[ind].back()] = numbers[b];
                dsu[ind].pop_back();
            }
        } else {
            concatenate(b, a);
        }
    }

    int count_components() const {
        int count = 0;
        for (const auto &v: dsu) {
            if (!v.empty()) {
                ++count;
            }
        }
        return count;
    }
};
