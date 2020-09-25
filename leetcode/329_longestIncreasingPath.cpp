// @File   : 329_longestIncreasingPath.cpp
// @Source : https://leetcode-cn.com/problems/longest-increasing-path-in-a-matrix/
// @Title  : 329. 矩阵中的最长递增路径
// @Auther : sun_ds
// @Date   : 2020/7/26

/**  题目描述：
    给定一个整数矩阵，找出最长递增路径的长度。

    对于每个单元格，你可以往上，下，左，右四个方向移动。 你不能在对角线方向上移动或移动到边界外（即不允许环绕）。

    示例 1:

    输入: nums =
    [
      [9,9,4],
      [6,6,8],
      [2,1,1]
    ]
    输出: 4
    解释: 最长递增路径为 [1, 2, 6, 9]。
    示例 2:

    输入: nums =
    [
      [3,4,5],
      [3,2,6],
      [2,2,1]
    ]
    输出: 4
    解释: 最长递增路径是 [3, 4, 5, 6]。注意不允许在对角线方向上移动。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/longest-increasing-path-in-a-matrix
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dfs + 记忆化
 * 以每个位置为起点进行 dfs。
 * 使用 memo 记录遍历过的位置的最大值(即以该点为起点的最长路径)
 * 每次遍历 上下左右 四个方向，满足不越界且大于当前值，进行递归。当前值的为起点的结果为四个方向中最大值加一。
 * 若当前 i，j 遍历过，直接返回 memo[i][j]
 * 最终得到各个位置的最大值即为矩阵中的最长路径长度。
 *
 * 时间复杂度：O(mn)，其中 m 和 n 分别是矩阵的行数和列数。深度优先搜索的时间复杂度是 O(V+E)，其中 V 是节点数，E 是边数。
 * 在矩阵中，O(V)=O(mn)，O(E)≈O(4mn)=O(mn)。
 * 空间复杂度：O(mn)，其中 m 和 n 分别是矩阵的行数和列数。
 * 空间复杂度主要取决于缓存和递归调用深度，缓存的空间复杂度是 O(mn)，递归调用深度不会超过 mn。
 *
 *
 * 2.拓扑排序 层序遍历
 * 从终点开始 bfs。统计层数即为结果。
 * 统计每个位置的出度(上下左右小于当前值的个数)。
 * 借助拓扑排序思想，出度为 0 的作为一层。
 * 并更新满足条件的的相邻位置，将下一层的出度为 0 的入队。
 * 最终，能够层序遍历的层数为结果。
 *
 *
 */

class Solution {
private:
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};
public:
    int dfs(vector<vector<int>>& matrix, int i, int j, vector<vector<int>>& memo) {
        if (memo[i][j] != -1) {
            return memo[i][j];
        }
        memo[i][j] = 1;
        for (int k = 0; k < 4; ++k) {
            int x = i + dx[k];
            int y = j + dy[k];
            if (x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size() && matrix[x][y] > matrix[i][j]) {
                memo[i][j] = max(memo[i][j], dfs(matrix, x, y, memo) + 1);
            }
        }
        return memo[i][j];
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> memo(m,vector<int>(n,-1));
        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                res = max(res, dfs(matrix, i, j, memo));
            }
        }
        return res;
    }
};


class Solution {
private:
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};
public:
    int longestIncreasingPath(vector< vector<int> > &matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return 0;
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> outdegrees(m, vector<int>(n,0));
        // 统计出度
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < 4; ++k) {
                    int x = i + dx[k], y = j + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] > matrix[i][j]) {
                        ++outdegrees[i][j];
                    }
                }
            }
        }
        queue <pair<int, int>> q;
        // 初始化，出度为 0 的为路径的终点，作为搜索的起点。
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (outdegrees[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }
        // 层序遍历
        int res = 0;
        while (!q.empty()) {
            ++res;
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                auto temp = q.front(); q.pop();
                int x = temp.first, y = temp.second;
                for (int k = 0; k < 4; ++k) {
                    int newX = x + dx[k], newY = y + dy[k];
                    if (newX >= 0 && newX < m && newY >= 0 && newY < n && matrix[newX][newY] < matrix[x][y]) {
                        --outdegrees[newX][newY];
                        // 作为下一层的起点
                        if (outdegrees[newX][newY] == 0) {
                            q.push({newX, newY});
                        }
                    }
                }
            }
        }
        return res;
    }
};


