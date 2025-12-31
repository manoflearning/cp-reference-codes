#include "../common/common.hpp"
// Erasable priority queue (lazy deletion).
// what: priority_queue with erase by value (multiset-like)
// time: push/pop/erase amortized O(log n), top O(1) amortized, memory: O(n)
// constraint: erase only existing values, duplicates ok
// usage: erasable_pq<ll> pq; pq.push(x); pq.erase(x); ll v = pq.top(); pq.pop();
template <class T, class O = less<T>>
struct pq_set {
    priority_queue<T, vector<T>, O> q, del;
    const T &top() const { return q.top(); }
    int size() const { return int(q.size() - del.size()); }
    bool empty() const { return !size(); }
    void insert(const T x) { q.push(x), flush(); }
    void pop() { q.pop(), flush(); }
    void erase(const T x) { del.push(x), flush(); }
    void flush() {
        while (del.size() && q.top() == del.top()) q.pop(), del.pop();
    }
};