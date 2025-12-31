#include "../common/common.hpp"

// what: erasable priority queue via lazy deletion.
// time: push/pop/erase O(log n); memory: O(n)
// constraint: erase assumes value exists; duplicates ok.
// usage: epq<ll> pq; pq.push(x); pq.erase(x); ll v = pq.top(); pq.pop();
template <class T, class cmp = less<T>>
struct epq {
    int cnt = 0;
    priority_queue<T, vector<T>, cmp> q, del;
    int size() const { return cnt; }
    bool empty() const { return cnt == 0; }
    const T &top() {
        fix();
        return q.top();
    }
    void push(const T &x) {
        q.push(x);
        cnt++;
    }
    void pop() {
        fix();
        if (q.empty()) return;
        q.pop();
        cnt--;
        fix();
    }
    void erase(const T &x) {
        del.push(x);
        cnt--;
    }
    void fix() {
        while (!del.empty() && !q.empty() && q.top() == del.top())
            q.pop(), del.pop();
    }
};
