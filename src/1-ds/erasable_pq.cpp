#include "../common/common.hpp"

// what: priority queue that supports deleting arbitrary values via lazy deletion.
// time: push/pop/erase O(log n); memory: O(n)
// constraint: erase/top/pop assume valid; duplicates ok.
// usage: erase_pq<ll> pq; pq.push(x); pq.erase(x); ll v = pq.top(); pq.pop();
template <class T, class cmp = less<T>>
struct erase_pq {
    priority_queue<T, vector<T>, cmp> q, del;
    int size() { return (int)q.size() - (int)del.size(); }
    bool empty() { return size() == 0; }
    const T &top() { return (fix(), q.top()); } // result: current extreme element.
    void push(const T &x) { q.push(x); }
    void pop() { fix(), q.pop(), fix(); }   // goal: remove one top element.
    void erase(const T &x) { del.push(x); } // goal: mark one x for deletion.
    void fix() {
        // invariant: q.top() is not marked deleted.
        while (!del.empty() && !q.empty() && q.top() == del.top()) q.pop(), del.pop();
    }
};
