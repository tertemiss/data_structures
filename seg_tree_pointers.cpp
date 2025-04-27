#include <iostream>
#include <vector>

#define int long long

const int inf = 1e9;

struct SegmentTree {
private:
    struct Node {
        int min, sum, max, set = inf, add = 0;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    Node* root;
    int size;

    void check(Node* v, int lm, int rm) {
        if (v->set != inf) {
            if (lm != rm) {
                if (!v->left) v->left = new Node;
                if (!v->right) v->right = new Node;
                v->left->set = v->set;
                v->right->set = v->set;
                v->left->add = 0;
                v->right->add = 0;
            }
            v->sum = (rm - lm + 1) * v->set;
            v->min = v->set;
            v->max = v->set;
            v->set = inf;
        }
        if (v->add != 0) {
            if (lm != rm) {
                if (!v->left) v->left = new Node;
                if (!v->right) v->right = new Node;
                v->left->add += v->add;
                v->right->add += v->add;
            }
            v->sum += (rm - lm + 1) * v->add;
            v->min += v->add;
            v->max += v->add;
            v->add = 0;
        }
    }

    void build(Node* v, int l, int r, const std::vector<int>& vec) {
        if (l == r) {
            v->sum = v->min = v->max = vec[l];
            return;
        }
        int m = (l + r) / 2;
        v->left = new Node;
        v->right = new Node;
        build(v->left, l, m, vec);
        build(v->right, m + 1, r, vec);
        v->sum = v->left->sum + v->right->sum;
        v->min = std::min(v->left->min, v->right->min);
        v->max = std::max(v->left->max, v->right->max);
    }

    void add(Node* v, int lm, int rm, int l, int r, int x) {
        check(v, lm, rm);
        if (lm > r || rm < l) return;
        if (lm >= l && rm <= r) {
            v->min += x;
            v->max += x;
            v->sum += (rm - lm + 1) * x;
            if (lm != rm) {
                if (!v->left) v->left = new Node;
                if (!v->right) v->right = new Node;
                v->left->add += x;
                v->right->add += x;
            }
            return;
        }
        int m = (lm + rm) / 2;
        if (!v->left) v->left = new Node;
        if (!v->right) v->right = new Node;
        add(v->left, lm, m, l, r, x);
        add(v->right, m + 1, rm, l, r, x);
        v->sum = v->left->sum + v->right->sum;
        v->min = std::min(v->left->min, v->right->min);
        v->max = std::max(v->left->max, v->right->max);
    }

    void set(Node* v, int lm, int rm, int l, int r, int x) {
        check(v, lm, rm);
        if (lm > r || rm < l) return;
        if (lm >= l && rm <= r) {
            v->min = v->max = x;
            v->sum = (rm - lm + 1) * x;
            v->add = 0;
            if (lm != rm) {
                if (!v->left) v->left = new Node;
                if (!v->right) v->right = new Node;
                v->left->set = x;
                v->right->set = x;
                v->left->add = 0;
                v->right->add = 0;
            }
            return;
        }
        int m = (lm + rm) / 2;
        if (!v->left) v->left = new Node;
        if (!v->right) v->right = new Node;
        set(v->left, lm, m, l, r, x);
        set(v->right, m + 1, rm, l, r, x);
        v->sum = v->left->sum + v->right->sum;
        v->min = std::min(v->left->min, v->right->min);
        v->max = std::max(v->left->max, v->right->max);
    }

    int get_min(Node* v, int lm, int rm, int l, int r) {
        check(v, lm, rm);
        if (lm > r || rm < l) return 1e18;
        if (lm >= l && rm <= r) return v->min;
        int m = (lm + rm) / 2;
        if (!v->left) v->left = new Node;
        if (!v->right) v->right = new Node;
        return std::min(get_min(v->left, lm, m, l, r), get_min(v->right, m + 1, rm, l, r));
    }

    int get_max(Node* v, int lm, int rm, int l, int r) {
        check(v, lm, rm);
        if (lm > r || rm < l) return -1e18;
        if (lm >= l && rm <= r) return v->max;
        int m = (lm + rm) / 2;
        if (!v->left) v->left = new Node;
        if (!v->right) v->right = new Node;
        return std::max(get_max(v->left, lm, m, l, r), get_max(v->right, m + 1, rm, l, r));
    }

    int get_sum(Node* v, int lm, int rm, int l, int r) {
        check(v, lm, rm);
        if (lm > r || rm < l) return 0;
        if (lm >= l && rm <= r) return v->sum;
        int m = (lm + rm) / 2;
        if (!v->left) v->left = new Node;
        if (!v->right) v->right = new Node;
        return get_sum(v->left, lm, m, l, r) + get_sum(v->right, m + 1, rm, l, r);
    }

public:
    SegmentTree(const std::vector<int>& vec) {
        size = vec.size();
        root = new Node;
        build(root, 0, size - 1, vec);
    }

    void range_add(int l, int r, int x) {
        add(root, 0, size - 1, l, r, x);
    }

    void range_set(int l, int r, int x) {
        set(root, 0, size - 1, l, r, x);
    }

    int range_min(int l, int r) {
        return get_min(root, 0, size - 1, l, r);
    }

    int range_max(int l, int r) {
        return get_max(root, 0, size - 1, l, r);
    }

    int range_sum(int l, int r) {
        return get_sum(root, 0, size - 1, l, r);
    }
};
