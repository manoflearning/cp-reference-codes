#include "../common/common.hpp"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
int main() {
  ordered_set os; // empty
  // basic usage
  os.insert(1); // 1
  os.insert(1); // 1
  os.insert(4); // 1 4
  os.insert(3); // 1 3 4
  os.insert(2); // 1 2 3 4
  os.insert(4); // 1 2 3 4
  os.erase(2);  // 1 3 4
  os.erase(2);  // 1 3 4
  os.insert(1); // 1 3 4
  os.erase(1);  // 3 4
  // order_of_key() (Assume os = {13, 32, 34, 45, 48, 59, 61, 68, 71, 78, 87, 128})
  cout << os.order_of_key(10) << '\n'; // 0
  cout << os.order_of_key(49) << '\n'; // 5
  cout << os.order_of_key(48) << '\n'; // 4
  // find_by_order() (Assume os = {13, 32, 34, 45, 48, 59, 61, 68, 71, 78, 87, 128})
  cout << *(os.find_by_order(0)) << '\n';   // 13
  cout << *(os.find_by_order(7)) << '\n';   // 68
  cout << *(os.find_by_order(100)) << '\n'; // 0
}