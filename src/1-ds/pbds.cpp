#include "../common/common.hpp"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;
ordered_set st;
st.order_of_key(x);  // number of elements strictly less than x
st.find_by_order(x); // value of xth element (0-based)