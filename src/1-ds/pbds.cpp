#include "../common/common.hpp"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// what: ordered set with order stats (no dup).
// time: insert/erase/order_of_key/find_by_order O(log n); memory: O(n)
// constraint: GNU pbds only.
// usage: oset s; s.order_of_key(x); s.find_by_order(k);
using oset = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;

// what: ordered multiset with order stats (dup ok).
// time: insert/erase/order_of_key/find_by_order O(log n); memory: O(n)
// constraint: GNU pbds only; erase assumes val exists.
// usage: omset s; m_erase(s, x);
using omset = tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update>;
void m_erase(omset &os, ll val) {
    int idx = os.order_of_key(val);
    omset::iterator it = os.find_by_order(idx);
    os.erase(it);
}
