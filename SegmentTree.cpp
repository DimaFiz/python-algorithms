#include <cstdint>
#include <vector>

// Gives you sum on a segment

struct SegmentTree {
    std::vector<int64_t> st;
    int ind_vec;


    int log(int n) {
        int degree = 0;
        while (1 << degree < n) {
            ++degree;
        }
        return degree;
    }

    SegmentTree(const std::vector<int> &numbers) {
        int degree = log(numbers.size());
        int len = (1 << (degree + 1)) - 1;
        ind_vec = (1 << degree) - 1;
        st.resize(len, -2e9);
        std::copy(numbers.begin(), numbers.end(), (st.begin() + ind_vec));

        for (int i = len - 1; i > 0; i -= 2) {
            st[(i - 1) / 2] = std::max(st[i], st[i - 1]);
        }
    }

    int64_t GetMax(int ind, int l, int r, int own_l, int own_r) {
        if (ind >= st.size() || r < own_l || l > own_r) {
            return -2e9;
        }
        if (l <= own_l && r >= own_r) {
            return st[ind];
        }
        return std::max(GetMax(2 * ind + 1, l, r, own_l, (own_l + own_r) / 2), GetMax(
                            2 * ind + 2, l, r, (own_l + own_r) / 2 + 1, own_r));
    }

    int64_t MaxFromSegment(int l, int r) {
        return GetMax(0, l, r, 0, ind_vec);
    }

    void Change(int cur_ind, int ch_ind, int x, int own_l, int own_r) {
        if (ch_ind > ind_vec || cur_ind > st.size()) {
            return;
        }
        if (cur_ind - ind_vec == ch_ind) {
            st[cur_ind] = x;
            return;
        }
        if ((own_l + own_r) / 2 >= ch_ind) {
            Change(2 * cur_ind + 1, ch_ind, x, own_l, (own_l + own_r) / 2);
        } else {
            Change(2 * cur_ind + 2, ch_ind, x, (own_l + own_r) / 2 + 1, own_r);
        }
        st[cur_ind] = std::max(st[2 * cur_ind + 1], st[2 * cur_ind + 2]);
    }

    void ChangeEl(int ind, int x) {
        Change(0, ind, x, 0, ind_vec);
    }
};
