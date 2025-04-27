#include <iostream>
#include <vector>

std::vector<long long> heap;

void sift_up(long long v) {
    while (v > 0 && heap[(v - 1) / 2] > heap[v]) {
        std::swap(heap[(v - 1) / 2], heap[v]);
        v = (v - 1) / 2;
    }
}

void sift_down(long long v) {
    long long n = heap.size();
    while (true) {
        long long u = v;
        if (2 * v + 1 < n && heap[2 * v + 1] < heap[u]) u = 2 * v + 1;
        if (2 * v + 2 < n && heap[2 * v + 2] < heap[u]) u = 2 * v + 2;
        if (u == v) break;
        std::swap(heap[v], heap[u]);
        v = u;
    }
}

void push(long long x) {
    heap.push_back(x);
    sift_up(heap.size() - 1);
}

long long top() {
    return heap[0];
}

void pop() {
    std::swap(heap[0], heap.back());
    heap.pop_back();
    if (!heap.empty()) sift_down(0);
}

bool empty() {
    return heap.empty();
}
