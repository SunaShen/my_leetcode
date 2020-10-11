// @File   : 834_sumOfDistancesInTree.cpp
// @Source : https://leetcode-cn.com/problems/sum-of-distances-in-tree/
// @Title  : 834. 树中距离之和
// @Auther : sun_ds
// @Date   : 2020/10/6

/**  题目描述：
    给定一个无向、连通的树。树中有 N 个标记为 0...N-1 的节点以及 N-1 条边 。

    第 i 条边连接节点 edges[i][0] 和 edges[i][1] 。

    返回一个表示节点 i 与其他所有节点距离之和的列表 ans。

    示例 1:

    输入: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
    输出: [8,12,6,10,10,10]
    解释:
    如下为给定的树的示意图：
      0
     / \
    1   2
       /|\
      3 4 5

    我们可以计算出 dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
    也就是 1 + 1 + 2 + 2 + 2 = 8。 因此，answer[0] = 8，以此类推。
    说明: 1 <= N <= 10000

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/sum-of-distances-in-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 树形动态规划
 *  考虑只求根节点到其他所有节点的距离之和
 *  定义 dp[u] 表示以 u 为根的子树，它的所有子节点到它的距离之和，同时定义 sz[u] 表示以 u 为根的子树的节点数量
 *  转移方程：
 *   dp[u] = sum(dp[v] + sz[v]) v = son(u) 其中 son[u] 表示 u 的所有后代节点集合
 *
 *  已知 v 的所有子节点到它的距离为 dp[v], 那么这些节点到 u 的距离都要考虑 边 u-v 的贡献。因此每个节点距离+1，共 sz[v] 个节点。
 *
 *  遍历使得各个节点都做一次根节点，则可获得各个节点到其他节点的距离之和。
 *  对于每个节点做一次树形动态规划，最终时间复杂度为 O(N^2)
 *
 *  进一步优化，考虑相邻节点转换成根节点能否利用之前状态。
 *
 *  考虑旋转树，将 v 作为根节点，u 相应的变为 v 的孩子。
 *  而此次转变中，除 v 和 u 节点之外，其他节点的 dp 和 sz 值都不变。
 *
 *  转换过后，v 不在 u 的 son[u] 中了，因此 u 节点的 dp 值要减去 v 的贡献。
 *  dp[u] = dp[u] - (dp[v] + sz[v])
 *  相应的 sz[u] = sz[u] - sz[v]
 *
 *  转换过后，v 的 son[v] 中多了新转换的 u ，因此 v 节点的 dp 值要加上新的 u 的贡献。
 *  dp[v] = dp[v] + (dp[u] + sz[u])
 *  相应的 sz[v] = sz[v] + sz[u]
 *
 *  时间复杂度 O(N)
 *  空间复杂度 O(N)
 *
 */

class Solution {
public:
    vector<int> ans, sz, dp;
    vector<vector<int>> graph;

    void dfs(int u, int f) {
        // 递归结束条件 没有除来的时候之外的边了。（叶子节点）
        sz[u] = 1;
        dp[u] = 0;

        for (auto& v: graph[u]) {
            // 不走回头路
            if (v == f) {
                continue;
            }
            dfs(v, u);
            // 更新 dp 和 sz
            dp[u] += dp[v] + sz[v];
            sz[u] += sz[v];
        }
    }

    void dfs2(int u, int f) {
        // 存储 结果
        ans[u] = dp[u];

        // 深度优先遍历
        // 递归结束条件 没有除来的时候之外的边了。（叶子节点）
        for (auto& v: graph[u]) {
            if (v == f) {
                continue;
            }
            // 保存当前状态
            int pu = dp[u], pv = dp[v];
            int su = sz[u], sv = sz[v];

            // 从 u 为根转为 v 为根，仅需修改 u 和 v 相关的 dp，sz

            // u 不当根节点了，而变成了 v 的孩子，因此 u 的需要减去 v 的贡献
            dp[u] -= dp[v] + sz[v];
            sz[u] -= sz[v];
            // v 不当孩子了，而变成了 u 的父亲，因此 v 的需要加上 u 的贡献(此时的 u 为更新过后的 u 即孩子 u)
            dp[v] += dp[u] + sz[u];
            sz[v] += sz[u];

            dfs2(v, u);

            // 回溯
            // 恢复状态，从另一个边递归下去
            dp[u] = pu, dp[v] = pv;
            sz[u] = su, sz[v] = sv;
        }
    }

    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        ans.resize(N, 0);
        sz.resize(N, 0);
        dp.resize(N, 0);
        graph.resize(N, {});
        // 无向图
        for (auto& edge: edges) {
            int u = edge[0], v = edge[1];
            graph[u].emplace_back(v);
            graph[v].emplace_back(u);
        }
        // 先以 0 为根，填充一遍 dp 和 sz
        dfs(0, -1);
        // 遍历所有节点，不断从之前状态转移过来
        dfs2(0, -1);
        return ans;
    }
};
