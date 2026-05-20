// Красно-черное дерево поиска

struct Node {
    static constexpr int INF = 1e9;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
    int value = INF;
    int color = 3;

private:
    bool am_i_left() {
        if (parent != nullptr && parent->left == this) {
            return true;
        }
        return false;
    }

public:
    Node() {
    }

    Node(Node *parent, int n) : parent(parent), color(2), value(n) {
    }

    void add(int n) {
        if (color == 3) {
            color = 1;
            value = n;
            return;
        }
        if (n == value) {
            return;
        }
        if (n < value) {
            if (left == nullptr) {
                left = new Node(this, n);
                left->fix();
            } else {
                left->add(n);
            }
        } else {
            if (right == nullptr) {
                right = new Node(this, n);
                right->fix();
            } else {
                right->add(n);
            }
        }
    }

    void fix() {
        if (parent == nullptr) {
            color = 1;
            return;
        }
        if (parent->color == 1) {
            return;
        }
        if (parent->am_i_left()) {
            if (parent->parent->right != nullptr && parent->parent->right->color == 2) {
                parent->parent->right->color = 1;
                parent->color = 1;
                parent->parent->color = 2;
                parent->parent->fix();
                return;
            } else {
                if (am_i_left()) {
                    {
                        auto g = parent->parent;
                        auto y = parent;
                        g->color = 2;
                        y->color = 1;
                        if (g->parent == nullptr) {
                        } else if (g->am_i_left()) {
                            g->parent->left = y;
                        } else {
                            g->parent->right = y;
                        }
                        y->parent = g->parent;
                        g->parent = y;
                        if (y->right != nullptr) y->right->parent = g;
                        g->left = y->right;
                        y->right = g;
                    }
                } else {
                    auto y = parent;
                    auto g = y->parent;
                    parent = g;
                    y->right = left;
                    if (left != nullptr) left->parent = y;
                    left = y;
                    g->left = this;
                    y->parent = this;
                    y->fix();
                }
            }
        } else {
            if (parent->parent->left != nullptr && parent->parent->left->color == 2) {
                parent->parent->left->color = 1;
                parent->color = 1;
                parent->parent->color = 2;
                parent->parent->fix();
                return;
            } else {
                if (!am_i_left()) {
                    {
                        auto g = parent->parent;
                        auto y = parent;
                        g->color = 2;
                        y->color = 1;
                        if (g->parent == nullptr) {
                        } else if (g->am_i_left()) {
                            g->parent->left = y;
                        } else {
                            g->parent->right = y;
                        }
                        y->parent = g->parent;
                        g->parent = y;
                        if (y->left != nullptr) y->left->parent = g;
                        g->right = y->left;
                        y->left = g;
                    }
                } else {
                    auto y = parent;
                    auto g = y->parent;
                    parent = g;
                    y->left = right;
                    if (right != nullptr) right->parent = y;
                    right = y;
                    g->right = this;
                    y->parent = this;
                    y->fix();
                }
            }
        }
    }

    bool find(int n) {
        if (n == value) {
            return true;
        }
        if (n > value) {
            if (right == nullptr) {
                return false;
            }
            return right->find(n);
        }
        if (left == nullptr) {
            return false;
        }
        return left->find(n);
    }

    Node *get_actual_root(Node *node) {
        if (node == nullptr) return nullptr;
        while (node->parent != nullptr) {
            node = node->parent;
        }
        return node;
    }

    void get_nodes() {
        std::cout << value << ' ';
        if (left != nullptr) {
            std::cout << left->value << ' ';
        } else {
            std::cout << "null" << ' ';
        }
        if (right != nullptr) {
            std::cout << right->value << ' ';
        } else {
            std::cout << "null" << ' ';
        }
        if (color == 2) {
            std::cout << "R" << '\n';
        } else {
            std::cout << "B" << '\n';
        }
        if (right != nullptr) {
            right->get_nodes();
        }
        if (left != nullptr) {
            left->get_nodes();
        }
    }

    ~Node() {
        delete left;
        delete right;
    }
};
