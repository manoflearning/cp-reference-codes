#include "../common/common.hpp"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// what: maintain a sorted set with order statistics (k-th / count < x) for distinct keys.
// time: insert/erase/order_of_key/find_by_order O(log n); memory: O(n)
// constraint: GNU pbds only.
// usage: oset s; s.order_of_key(x); s.find_by_order(k);
using oset = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;

// what: maintain a sorted multiset with order statistics (k-th / count < x) via unique ids.
// time: insert/erase/order_of_key/find_by_order O(log n); memory: O(n)
// constraint: GNU pbds only; erase assumes val exists.
// usage: omset s; m_insert(s, x); m_erase(s, x); int k=m_order(s,x); ll v=m_kth(s,i);
using omset = tree<pll, null_type, less<pll>, rb_tree_tag, tree_order_statistics_node_update>;
static ll om_uid = 0;

void m_insert(omset &os, ll val) {
    // goal: insert one occurrence of val.
    os.insert({val, om_uid++});
}
void m_erase(omset &os, ll val) {
    // goal: erase one occurrence of val.
    auto it = os.lower_bound({val, LLONG_MIN});
    os.erase(it);
}
int m_order(const omset &os, ll val) {
    // result: number of elements strictly less than val.
    return os.order_of_key({val, LLONG_MIN});
}
ll m_kth(const omset &os, int k) {
    // result: k-th value (0-indexed) by order.
    return os.find_by_order(k)->fr;
}
