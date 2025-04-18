# CP Reference Codes
My implementations of various data structures and algorithms for competitive programming.

<!-- ## Contents
1. [Data Structure](https://github.com/manoflearning/cp-reference-codes/tree/master/1-data-structure) <br>
1.1. [Union Find](https://github.com/manoflearning/cp-reference-codes/blob/master/1-data-structure/union_find.cpp) <br>
1.2. [Segment Tree](https://github.com/manoflearning/cp-reference-codes/tree/master/1-data-structure/segment_tree.cpp) <br>
1.3. [Merge Sort Tree](https://github.com/manoflearning/cp-reference-codes/tree/master/1-data-structure/merge_sort_tree.cpp) <br>
1.4. [Fenwick Tree](https://github.com/manoflearning/cp-reference-codes/tree/master/1-data-structure/fenwick_tree.cpp) <br>
1.5. [Li Chao Tree](https://github.com/manoflearning/cp-reference-codes/tree/master/1-data-structure/li_chao_tree.cpp) <br>
2. [Graph](https://github.com/manoflearning/cp-reference-codes/tree/master/2-graph) <br>
2.1. [Dijkstra's, Bellman-Ford, Floyd-Warshall](https://github.com/manoflearning/cp-reference-codes/blob/master/2-graph/dijkstra_bellman_ford_floyd_warshall.cpp) <br>
2.2. [Minimum Spanning Tree](https://github.com/manoflearning/cp-reference-codes/blob/master/2-graph/minimum_spanning_tree.cpp) <br>
2.3. [Topological Sort](https://github.com/manoflearning/cp-reference-codes/tree/master/2-graph/topological_sort.cpp) <br>
2.4. [SCC, 2-SAT](https://github.com/manoflearning/cp-reference-codes/tree/master/2-graph/scc_2_sat.cpp) <br>
2.5. [BCC](https://github.com/manoflearning/cp-reference-codes/blob/master/2-graph/bcc.cpp) <br>
2.6. [Euler Circuit](https://github.com/manoflearning/cp-reference-codes/blob/master/2-graph/euler_circuit.cpp) <br>
3. [Tree](https://github.com/manoflearning/cp-reference-codes/tree/master/3-tree) <br>
3.1. [LCA in O(logN) (Sparse Table)](https://github.com/manoflearning/cp-reference-codes/blob/master/3-tree/lca_in_o_logn_sparse_table.cpp) <br>
3.2. [Euler Tour Technique](https://github.com/manoflearning/cp-reference-codes/tree/master/3-tree/euler_tour_technique.cpp) <br>
3.3. [Heavy-Light Decomposition](https://github.com/manoflearning/cp-reference-codes/tree/master/3-tree/heavy_light_decomposition.cpp) <br>
3.4. [Centroid Decomposition](https://github.com/manoflearning/cp-reference-codes/blob/master/3-tree/centroid_decomposition.cpp) <br>
4. [Network Flow](https://github.com/manoflearning/cp-reference-codes/tree/master/4-network-flow) <br>
4.1. [Maximum Flow](https://github.com/manoflearning/cp-reference-codes/tree/master/4-network-flow/maximum_flow.cpp) <br>
4.2. [Dinic's Algorithm](https://github.com/manoflearning/cp-reference-codes/blob/master/4-network-flow/dinics_algorithm.cpp) <br>
4.3. [Bipartite Matching](https://github.com/manoflearning/cp-reference-codes/blob/master/4-network-flow/bipartite_matching.cpp) <br>
4.4. [Hopcroft-Karp Algorithm](https://github.com/manoflearning/cp-reference-codes/blob/master/4-network-flow/hopcroft_karp_algorithm.cpp) <br>
4.5. [MCMF](https://github.com/manoflearning/cp-reference-codes/blob/master/4-network-flow/mcmf.cpp) <br>
5. [String](https://github.com/manoflearning/cp-reference-codes/tree/master/5-string) <br>
5.1. [Rabin-Karp Algorithm](https://github.com/manoflearning/cp-reference-codes/tree/master/5-string/rabin_karp_algorithm.cpp) <br>
5.2. [KMP Algorithm](https://github.com/manoflearning/cp-reference-codes/blob/master/5-string/kmp_algorithm.cpp) <br>
5.3. [Trie](https://github.com/manoflearning/cp-reference-codes/tree/master/5-string/trie.cpp) <br>
5.4. [Aho-Corasick](https://github.com/manoflearning/cp-reference-codes/blob/master/5-string/aho_corasick.cpp) <br>
5.5. [Suffix Array](https://github.com/manoflearning/cp-reference-codes/blob/master/5-string/suffix_array.cpp) <br>
5.6. [Manacher's Algorithm](https://github.com/manoflearning/cp-reference-codes/blob/master/5-string/manachers_algorithm.cpp) <br>
5.7. [Z Algorithm](https://github.com/manoflearning/cp-reference-codes/blob/master/5-string/z_algorithm.cpp) <br>
6. [Geometry](https://github.com/manoflearning/cp-reference-codes/tree/master/6-geometry) <br>
6.1. [CCW Algorithm](https://github.com/manoflearning/cp-reference-codes/blob/master/6-geometry/ccw_algorithm.cpp) <br>
6.2. [Convex Hull](https://github.com/manoflearning/cp-reference-codes/tree/master/6-geometry/convex_hull.cpp) <br>
6.3. [Rotating Callipers](https://github.com/manoflearning/cp-reference-codes/blob/master/6-geometry/rotating_callipers.cpp) <br>
6.4. [Ray Casting](https://github.com/manoflearning/cp-reference-codes/blob/master/6-geometry/ray_casting.cpp) <br>
6.5. [Sort by Angular](https://github.com/manoflearning/cp-reference-codes/blob/master/6-geometry/sort_by_angular.cpp) <br>
6.6. [Bulldozer Trick](https://github.com/manoflearning/cp-reference-codes/blob/master/6-geometry/bulldozer_trick.cpp) <br>
6.7. [Minimum Enclosing Circle](https://github.com/manoflearning/cp-reference-codes/blob/master/6-geometry/minimum_enclosing_circle.cpp) <br>
7. [Math](https://github.com/manoflearning/cp-reference-codes/tree/master/7-math) <br>
7.1. [Basic Sqrt-Time Algorithms](https://github.com/manoflearning/cp-reference-codes/tree/master/7-math/basic_sqrt_time_algorithms.cpp) <br>
7.2. [Sieve](https://github.com/manoflearning/cp-reference-codes/blob/master/7-math/sieve.cpp) <br>
7.3. [Euclidean Algorithms](https://github.com/manoflearning/cp-reference-codes/blob/master/7-math/euclidean_algorithms.cpp) <br>
7.4. [Fermat's Little Theorem](https://github.com/manoflearning/cp-reference-codes/blob/master/7-math/fermats_little_theorem.cpp) <br>
7.5. [Euler's Phi Function](https://github.com/manoflearning/cp-reference-codes/blob/master/7-math/eulers_phi_function.cpp) <br>
7.6. [Chinese Remainder Theorem](https://github.com/manoflearning/cp-reference-codes/blob/master/7-math/chinese_remainder_theorem.cpp) <br>
7.7. [Binomial Coefficient](https://github.com/manoflearning/cp-reference-codes/blob/master/7-math/binomial_coefficient.cpp) <br>
7.8. [Matrix](https://github.com/manoflearning/cp-reference-codes/blob/master/7-math/matrix.cpp) <br>
7.9. [Catalan Number, Derangement Number](https://github.com/manoflearning/cp-reference-codes/blob/master/7-math/catalan_number_derangement_number.cpp) <br>
7.10. [FFT](https://github.com/manoflearning/cp-reference-codes/blob/master/7-math/fft.cpp) <br>
7.11. [Gauss-Jordan Elimination](https://github.com/manoflearning/cp-reference-codes/blob/master/7-math/gauss_jordan_elimination.cpp) <br>
7.12. [Miller-Rabin Test, Pollard Rho Factorization](https://github.com/manoflearning/cp-reference-codes/blob/master/7-math/miller_rabin_pollard_rho.cpp) <br>

8. [Misc](https://github.com/manoflearning/cp-reference-codes/tree/master/8-misc) <br>
8.1. [Coordinate Compression](https://github.com/manoflearning/cp-reference-codes/blob/master/8-misc/coordinate_compression.cpp) <br>
8.2. [2D Prefix Sum](https://github.com/manoflearning/cp-reference-codes/blob/master/8-misc/2d_prefix_sum.cpp) <br>
8.3. [DP Opt](https://github.com/manoflearning/cp-reference-codes/blob/master/8-misc/dp_opt.cpp) <br>
8.4. [Sqrt Decomposition, Mo's Algorithm](https://github.com/manoflearning/cp-reference-codes/blob/master/8-misc/sqrt_decomposition_mos_algorithm.cpp) <br>
8.5. [Fraction Data Type](https://github.com/manoflearning/cp-reference-codes/blob/master/8-misc/fraction_data_type.cpp) <br>
8.6. [Rotation Matrix, Manhattan Distance, Chebyshev Distance](https://github.com/manoflearning/cp-reference-codes/blob/master/8-misc/rotation_matrix_manhattan_distance_chebyshev_distance.txt) <br>
8.7. [Random](https://github.com/manoflearning/cp-reference-codes/blob/master/8-misc/random.cpp) <br>
8.8. [Ternary Search](https://github.com/manoflearning/cp-reference-codes/blob/master/8-misc/ternary_search.cpp) <br>
8.9. [LIS in O(NlogN)](https://github.com/manoflearning/cp-reference-codes/tree/master/8-misc/lis_in_o_nlogn.cpp) <br>
8.10. [System of Difference Constraints](https://github.com/manoflearning/cp-reference-codes/blob/master/8-misc/system_of_difference_constraints.cpp) <br>
8.11. [SIMD](https://github.com/manoflearning/cp-reference-codes/blob/master/8-misc/simd.cpp) <br> -->
