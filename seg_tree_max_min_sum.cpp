#include <iostream>
#include <vector>

#define int long long

const int inf = 1e9;

struct chel {
    int min, sum, max, set = inf, add = 0;
};

void check(int v, int lm, int rm, std::vector<chel>& seg) {
    if (seg[v].set != inf) {
        if (lm != rm) {
            seg[v * 2 + 1].set = seg[v].set;
            seg[v * 2 + 2].set = seg[v].set;
            seg[v * 2 + 1].add = 0;
            seg[v * 2 + 2].add = 0;
            
        }
        seg[v].sum = (rm - lm + 1) * seg[v].set;
        seg[v].min = seg[v].set;
        seg[v].max = seg[v].set;
        seg[v].set = inf;
    }
    if (seg[v].add != 0) {
        if (lm != rm) {
            seg[v * 2 + 1].add += seg[v].add;
            seg[v * 2 + 2].add += seg[v].add;
        }
        seg[v].sum += (rm - lm + 1) * seg[v].add;
        seg[v].min += seg[v].add;
        seg[v].max += seg[v].add;
        seg[v].add = 0;
    }
}

void build(int v, int l, int r, std::vector<int>& vec, std::vector<chel>& seg) {
    if (l == r) {
        seg[v] = {vec[l], vec[l], vec[l]};
        return;
    }
    int m = (l + r) / 2;
    build(v * 2 + 1, l, m, vec, seg);
    build(v * 2 + 2, m + 1, r, vec, seg);
    seg[v].sum = seg[v * 2 + 1].sum + seg[v * 2 + 2].sum;
    seg[v].max = std::max(seg[v * 2 + 1].max, seg[v * 2 + 2].max);
    seg[v].min = std::min(seg[v * 2 + 1].min, seg[v * 2 + 2].min);
}

void add(int v, int lm, int rm, int l, int r, int x, std::vector<chel>& seg) {
    check(v, lm, rm, seg);
    if (lm > r || rm < l) return;
    if (lm >= l && rm <= r) {
        seg[v].max += x;
        seg[v].min += x;
        seg[v].sum += (rm - lm + 1) * x;
        if (lm != rm) {
            seg[v * 2 + 1].add += x;
            seg[v * 2 + 2].add += x;
        }
        return;
    }
    int m = (lm + rm) / 2;
    add(v * 2 + 1, lm, m, l, r, x, seg);
    add(v * 2 + 2, m + 1, rm, l, r, x, seg);
    seg[v].sum = seg[v * 2 + 1].sum + seg[v * 2 + 2].sum;
    seg[v].max = std::max(seg[v * 2 + 1].max, seg[v * 2 + 2].max);
    seg[v].min = std::min(seg[v * 2 + 1].min, seg[v * 2 + 2].min);
}

void set(int v, int lm, int rm, int l, int r, int x, std::vector<chel>& seg) {
    check(v, lm, rm, seg);
    if (lm > r || rm < l) return;
    if (lm >= l && rm <= r) {
        seg[v].max = x;
        seg[v].min = x;
        seg[v].sum = (rm - lm + 1) * x;
        seg[v].add = 0;
        if (lm != rm) {
            seg[v * 2 + 1].set = x;
            seg[v * 2 + 2].set = x;
            seg[v * 2 + 1].add = 0;
            seg[v * 2 + 2].add = 0;
        }
        return;
    }
    int m = (lm + rm) / 2;
    set(v * 2 + 1, lm, m, l, r, x, seg);
    set(v * 2 + 2, m + 1, rm, l, r, x, seg);
    seg[v].sum = seg[v * 2 + 1].sum + seg[v * 2 + 2].sum;
    seg[v].max = std::max(seg[v * 2 + 1].max, seg[v * 2 + 2].max);
    seg[v].min = std::min(seg[v * 2 + 1].min, seg[v * 2 + 2].min);
}

int get_min(int v, int lm, int rm, int l, int r, std::vector<chel>& seg) {
    check(v, lm, rm, seg);
    if (lm > r || rm < l) return 1e18;
    if (lm >= l && rm <= r) {
        return seg[v].min;
    }
    int m = (lm + rm) / 2;
    int a = get_min(v * 2 + 1, lm, m, l, r, seg);
    int b = get_min(v * 2 + 2, m + 1, rm, l, r, seg);
    return std::min(a, b);
}

int get_max(int v, int lm, int rm, int l, int r, std::vector<chel>& seg) {
    check(v, lm, rm, seg);
    if (lm > r || rm < l) return -1e18;
    if (lm >= l && rm <= r) {
        return seg[v].max;
    }
    int m = (lm + rm) / 2;
    int a = get_max(v * 2 + 1, lm, m, l, r, seg);
    int b = get_max(v * 2 + 2, m + 1, rm, l, r, seg);
    return std::max(a, b);
}

int get_sum(int v, int lm, int rm, int l, int r, std::vector<chel>& seg) {
    check(v, lm, rm, seg);
    if (lm > r || rm < l) return 0;
    if (lm >= l && rm <= r) {
        return seg[v].sum;
    }
    int m = (lm + rm) / 2;
    int a = get_sum(v * 2 + 1, lm, m, l, r, seg);
    int b = get_sum(v * 2 + 2, m + 1, rm, l, r, seg);
    return a + b;
}
