#include <utility>
#include <cmath>

struct Treap {
    struct Node {
        Node *left = nullptr;
        Node *right = nullptr;
        int x;
        int y;

        Node(int x, int y) : x(x), y(y) {
        }

        ~Node() {
            delete left;
            delete right;
        }
    };

private:
    Node *root = nullptr;

public:
    std::pair<Node *, Node *> split(Node *node, int x) {
        if (node == nullptr) {
            return {nullptr, nullptr};
        }
        if (node->x < x) {
            auto [l, r] = split(node->right, x);
            node->right = l;
            return {node, r};
        }
        auto [l, r] = split(node->left, x);
        node->left = r;
        return {l, node};
    }

    Node *merge(Node *A, Node *B) {
        if (A == nullptr) {
            return B;
        }
        if (B == nullptr) {
            return A;
        }
        if (B->y < A->y) {
            A->right = merge(A->right, B);
            return A;
        } else {
            B->left = merge(A, B->left);
            return B;
        }
    }

    Node *add(Node *node, int x, int y) {
        if (node == nullptr) {
            return new Node(x, y);
        }
        if (node->y < y) {
            Node *new_root = new Node(x, y);
            auto [l, r] = split(node, x);
            new_root->left = l;
            new_root->right = r;
            return new_root;
        }
        if (node->x < x) {
            node->right = add(node->right, x, y);
            return node;
        }
        node->left = add(node->left, x, y);
        return node;
    }

    void insert(int x, int y) {
        root = add(root, x, y);
    }

    void Delete(int x) {
        auto [l1, r1] = split(root, x);
        auto [l2, r2] = split(r1, x + 1);
        root = merge(l1, r2);
    }

    int Contains(Node *node, int x) {
        if (node == nullptr) {
            return -1;
        }
        if (x == node->x) {
            return 0;
        }
        if (x < node->x) {
            int h = Contains(node->left, x);
            if (h == -1) {
                return -1;
            } else {
                return h + 1;
            }
        }
        int h = Contains(node->right, x);
        if (h == -1) {
            return -1;
        } else {
            return h + 1;
        }
    }

    int get_deep(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        int h;
        h = std::max(get_deep(node->left), get_deep(node->right));
        return h + 1;
    }

    int get_deep_from_root() {
        return get_deep(root);
    }


    int find(int x) {
        return Contains(root, x);
    }
};
