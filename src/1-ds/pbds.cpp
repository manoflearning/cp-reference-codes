#include "../common/common.hpp"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using pbds = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;
pbds st;
st.order_of_key(x);  // number of elements strictly less than x
st.find_by_order(x); // value of xth element (0-based)

// multiset pbds (use "less_equal<int>" and custom "m_erase")
using multi_pbds = tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>;
void m_erase(multi_pbds &OS, int val) {
    int index = OS.order_of_key(val);
    multi_pbds::iterator it = OS.find_by_order(index);
    OS.erase(it);
}
