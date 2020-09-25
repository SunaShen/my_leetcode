// @File   : 685_findRedundantDirectedConnection.cpp
// @Source : https://leetcode-cn.com/problems/redundant-connection-ii/
// @Title  : 685. 冗余连接 II
// @Auther : sun_ds
// @Date   : 2020/9/17

/**  题目描述：
    在本问题中，有根树指满足以下条件的有向图。该树只有一个根节点，所有其他节点都是该根节点的后继。每一个节点只有一个父节点，除了根节点没有父节点。

    输入一个有向图，该图由一个有着N个节点 (节点值不重复1, 2, ..., N) 的树及一条附加的边构成。附加的边的两个顶点包含在1到N中间，这条附加的边不属于树中已存在的边。

    结果图是一个以边组成的二维数组。 每一个边 的元素是一对 [u, v]，用以表示有向图中连接顶点 u 和顶点 v 的边，其中 u 是 v 的一个父节点。

    返回一条能删除的边，使得剩下的图是有N个节点的有根树。若有多个答案，返回最后出现在给定二维数组的答案。

    示例 1:

    输入: [[1,2], [1,3], [2,3]]
    输出: [2,3]
    解释: 给定的有向图如下:
      1
     / \
    v   v
    2-->3
    示例 2:

    输入: [[1,2], [2,3], [3,4], [4,1], [1,5]]
    输出: [4,1]
    解释: 给定的有向图如下:
    5 <- 1 -> 2
         ^    |
         |    v
         4 <- 3
    注意:

    二维数组大小的在3到1000范围内。
    二维数组中的每个整数在1到N之间，其中 N 是二维数组的大小。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/redundant-connection-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.并查集
 * 在一棵树中，边的数量比节点的数量少 1。如果一棵树有 N 个节点，则这棵树有 N−1 条边。
 * 这道题中的图在树的基础上多了一条附加的边，因此边的数量也是 N。
 *
 * 树中的每个节点都有一个父节点，除了根节点没有父节点。在多了一条附加的边之后，可能有以下两种情况：
 *  1) 附加的边指向根节点，则包括根节点在内的每个节点都有一个父节点，此时图中一定有环路；
 *  2) 附加的边指向非根节点，则恰好有一个节点（即被附加的边指向的节点）有两个父节点，此时图中可能有环路也可能没有环路。
 *
 * 要找到附加的边，需要遍历图中的所有的边构建出一棵树，在构建树的过程中寻找导致冲突（即导致一个节点有两个父节点）的边以及导致环路出现的边。
 * (指向根节点只有环路，没有两个父节点， 指向非根节点一定有两个父节点，但不一定有环路)
 * 具体做法是，使用数组 parent 记录每个节点的父节点，初始时对于任何 1≤i≤N 都有 parent[i]=i，另外创建并查集，初始时并查集中的每个节点都是一个连通分支，该连通分支的根节点就是该节点本身。
 * 遍历每条边的过程中，维护导致冲突的边和导致环路出现的边，由于只有一条附加的边，因此最多有一条导致冲突的边和一条导致环路出现的边。
 *
 * 当访问到边 [u,v] 时，进行如下操作：
 *  如果此时已经有 parent[v] != v ，说明 v 有两个父节点，将当前的边 [u,v] 记为导致冲突的边；
 *  否则，令 parent[v]=u，然后在并查集中分别找到 u 和 v 的祖先（即各自的连通分支中的根节点），如果祖先相同，说明这条边导致环路出现，将当前的边 [u,v] 记为导致环路出现的边，如果祖先不同，则在并查集中将 u 和 v 进行合并。
 *
 * 根据上述操作，同一条边不可能同时被记为导致冲突的边和导致环路出现的边。如果访问到的边确实同时导致冲突和环路出现，则这条边被记为导致冲突的边。
 *
 * 在遍历图中的所有边之后，根据是否存在导致冲突的边和导致环路出现的边，得到附加的边。
 *
 * 如果没有导致冲突的边，说明附加的边一定导致环路出现，而且是在环路中的最后一条被访问到的边，因此附加的边即为导致环路出现的边。 (指向根节点的情况)
 * 如果有导致冲突的边，记这条边为 [u,v]，则有两条边指向 v，另一条边为 [parent[v],v]，需要通过判断是否有导致环路的边决定哪条边是附加的边。
 *  如果有导致环路的边，则附加的边不可能是 [u,v]（因为 [u,v] 已经被记为导致冲突的边，不可能被记为导致环路出现的边），因此附加的边是 [parent[v],v]。
 *  如果没有导致环路的边，则附加的边是后被访问到的指向 v 的边，因此附加的边是 [u,v]。
 *
 *
 * 时间复杂度：O(NlogN)
 * 空间复杂度：O(N)
 *
 *
 * 作者：LeetCode-Solution
 * 链接：https://leetcode-cn.com/problems/redundant-connection-ii/solution/rong-yu-lian-jie-ii-by-leetcode-solution/
 * 来源：力扣（LeetCode）
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 */

// 并查集
struct UnionFind {
    vector <int> ancestor;

    UnionFind(int n) {
        ancestor.resize(n);
        for (int i = 0; i < n; ++i) {
            ancestor[i] = i;
        }
    }

    int find(int index) {
        return index == ancestor[index] ? index : ancestor[index] = find(ancestor[index]);
    }

    void merge(int u, int v) {
        ancestor[find(u)] = find(v);
    }
};

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int nodesCount = edges.size();
        // 两个并查集
        // uf 和 parent, parent 也勉强算一个并查集(不路径压缩的，存储直接相连的父节点)
        UnionFind uf = UnionFind(nodesCount + 1);
        auto parent = vector<int>(nodesCount + 1);
        for (int i = 1; i <= nodesCount; ++i) {
            parent[i] = i;
        }
        int conflict = -1;
        int cycle = -1;
        for (int i = 0; i < nodesCount; ++i) {
            auto edge = edges[i];
            int node1 = edge[0], node2 = edge[1];
            if (parent[node2] != node2) {
                // 边冲突，附加边二选一
                conflict = i;
            } else {
                // 环，指向根节点
                parent[node2] = node1;
                if (uf.find(node1) == uf.find(node2)) {
                    cycle = i;
                } else {
                    uf.merge(node1, node2);
                }
            }
        }
        if (conflict < 0) {
            // 指向根节点
            auto redundant = vector<int> {edges[cycle][0], edges[cycle][1]};
            return redundant;
        } else {
            auto conflictEdge = edges[conflict];
            // 指向非根节点，导致节点有两个父节点

            // 说明添加当前边之前就有环了，不是当前边引起的那就是另一个父节点的边
            if (cycle >= 0) {
                auto redundant = vector<int> {parent[conflictEdge[1]], conflictEdge[1]};
                return redundant;
            } else {
                // 说明添加当前边之前没有环，就是当前边引起的
                auto redundant = vector<int> {conflictEdge[0], conflictEdge[1]};
                return redundant;
            }
        }
    }
};

