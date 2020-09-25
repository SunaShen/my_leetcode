// @File   : LCP13_minimalSteps.cpp
// @Source : https://leetcode-cn.com/problems/xun-bao/
// @Title  : LCP 13. 寻宝
// @Auther : sun_ds
// @Date   : 2020/7/29

/**  题目描述：
    我们得到了一副藏宝图，藏宝图显示，在一个迷宫中存在着未被世人发现的宝藏。

    迷宫是一个二维矩阵，用一个字符串数组表示。它标识了唯一的入口（用 'S' 表示），和唯一的宝藏地点（用 'T' 表示）。但是，宝藏被一些隐蔽的机关保护了起来。在地图上有若干个机关点（用 'M' 表示），只有所有机关均被触发，才可以拿到宝藏。

    要保持机关的触发，需要把一个重石放在上面。迷宫中有若干个石堆（用 'O' 表示），每个石堆都有无限个足够触发机关的重石。但是由于石头太重，我们一次只能搬一个石头到指定地点。

    迷宫中同样有一些墙壁（用 '#' 表示），我们不能走入墙壁。剩余的都是可随意通行的点（用 '.' 表示）。石堆、机关、起点和终点（无论是否能拿到宝藏）也是可以通行的。

    我们每步可以选择向上/向下/向左/向右移动一格，并且不能移出迷宫。搬起石头和放下石头不算步数。那么，从起点开始，我们最少需要多少步才能最后拿到宝藏呢？如果无法拿到宝藏，返回 -1 。

    示例 1：

    输入： ["S#O", "M..", "M.T"]

    输出：16

    解释：最优路线为： S->O, cost = 4, 去搬石头 O->第二行的M, cost = 3, M机关触发 第二行的M->O, cost = 3, 我们需要继续回去 O 搬石头。 O->第三行的M, cost = 4, 此时所有机关均触发 第三行的M->T, cost = 2，去T点拿宝藏。 总步数为16。

    示例 2：

    输入： ["S#O", "M.#", "M.T"]

    输出：-1

    解释：我们无法搬到石头触发机关

    示例 3：

    输入： ["S#O", "M.T", "M.."]

    输出：17

    解释：注意终点也是可以通行的。

    限制：

    1 <= maze.length <= 100
    1 <= maze[i].length <= 100
    maze[i].length == maze[j].length
    S 和 T 有且只有一个
    0 <= M的数量 <= 16
    0 <= O的数量 <= 40，题目保证当迷宫中存在 M 时，一定存在至少一个 O 。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/xun-bao
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 状态压缩动态规划
 *
 * 起点：S
 * 终点：T
 * 机关：M
 * 石头：O
 *
 * 分析走法情况：
 *  1）从 S 走到 O，我们不会从 S 直接走到 M，因为触发机关要先搬石头   (第一次)
 *  2）从 O 走到 M
 *  3）从 M 走到 O
 *  4）从 M 走到 T
 *
 * 提前计算出S,T,M,O各个点之间的距离。
 *  计算 S 到各个点的距离， 计算各个 M 到各个 O 的距离，计算各个 M 到 T 的距离。
 *  S-O-M
 *      选中 M,枚举 O，得到 S-O-M 的最短路径。
 *  M-O-M'
 *      选中 M'，枚举 O，得到 M-O-M'的最短路径。
 *
 *
 *  dp.
 *  使用 mask 压缩表示触发状态。二进制 1 表示触发，二进制 0 表示未触发。mask=0000 1100 0001 0001 表示 触发的集合为 T = {M1,M5,M11,M12}
 *  定义 f(mask,i) 表示当前处于第 i 个 M 处，触发状态为 mask 的最小步数。mask 代表已经触发的集合。
 *  因此，f(mask,i) 可以从前一个mask(不包含触发 i 的状态）转移过来。不知道哪一个最小，穷举。
 *  f(mask,i) = min{f(mask xor (2^i), j) + d[j,i]}; 其中 j 为 mask xor (2^i) 中的集合。即 mask 中除了 i 之外的已经触发的机关。
 *
 *  初始化，第一个机关以 S-O-M 路径到达。
 *
 *  最终得到 dp[final_mask][i] 其中final_mask表示所有机关被触发。
 *  此时最终结果为 dp[final_mask][i] + dist(Mi , T)
 *
 * 假设迷宫的面积为 s，M 的数量为 m，O 的数量为 o。
 *
 * 时间复杂度度 O(m*s+m^2*o+2^m*m^2)
 *  一次 bfs 代价 O(s)，m 次 bfs 代价为 O(ms).
 *  预处理任意两个 M 经过 O 的最短距离时间代价是 O(m^2*o).
 *  动态规划时间代价为 O(2^m*m^2)
 * 空间复杂度 O(s+bs+2^m*m)
 *  bfs 队列空间代价为 O(s)
 *  预处理 Mi 到各个点的最短距离的空间代价为 O(bs)
 *  动态规划数组的空间代价为O(2^m*m)
 *
 *
 *
 *
 * 这道题是一个非常经典的状态压缩动态规划模型：有 n 个任务 {M1,M2,M3,...Mn}
 * 每两个任务之间有一个 c(Mi,Mj) 表示在 Mi 之后（下一个）做 Mj 的花费，让你求解把 n 个任务都做完需要的最小花费。通常这个 n 会非常的小，因为需要构造2^n种状态
 * c(Mi,Mj) 可能是题目给出，也可能是可以在很短的时间内计算出来的一个值。
 * 这类问题的状态设计一般都是 f(mask,i) 表示当前任务完成的状态是 mask，当前位置是 i，考虑转移的时候我们只需要考虑当前任务的上一个任务即可.
 * 作者：LeetCode-Solution
 * 链接：https://leetcode-cn.com/problems/xun-bao/solution/xun-bao-bfs-dp-by-leetcode-solution/
 * 来源：力扣（LeetCode）
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 */

class Solution {
public:
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    int n, m;

    bool inBound(int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    }

    vector<vector<int>> bfs(int x, int y, vector<string>& maze) {
        vector<vector<int>> ret(n, vector<int>(m, -1));
        ret[x][y] = 0;
        queue<pair<int, int>> Q;
        Q.push({x, y});
        while (!Q.empty()) {
            auto p = Q.front();
            Q.pop();
            int x = p.first, y = p.second;
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k], ny = y + dy[k];
                if (inBound(nx, ny) && maze[nx][ny] != '#' && ret[nx][ny] == -1) {
                    ret[nx][ny] = ret[x][y] + 1;
                    Q.push({nx, ny});
                }
            }
        }
        return ret;
    }

    int minimalSteps(vector<string>& maze) {
        n = maze.size(), m = maze[0].size();
        // 机关 & 石头
        vector<pair<int, int>> buttons, stones;
        // 起点 & 终点
        int sx, sy, tx, ty;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (maze[i][j] == 'M') {
                    buttons.push_back({i, j});
                }
                if (maze[i][j] == 'O') {
                    stones.push_back({i, j});
                }
                if (maze[i][j] == 'S') {
                    sx = i, sy = j;
                }
                if (maze[i][j] == 'T') {
                    tx = i, ty = j;
                }
            }
        }
        int nb = buttons.size();
        int ns = stones.size();
        vector<vector<int>> start_dist = bfs(sx, sy, maze);

        // 边界情况：没有机关
        if (nb == 0) {
            return start_dist[tx][ty];
        }
        // 从某个机关到其他机关 / 起点与终点的最短距离。
        vector<vector<int>> dist(nb, vector<int>(nb + 2, -1));
        // 中间结果
        vector<vector<vector<int>>> dd(nb);
        for (int i = 0; i < nb; i++) {
            vector<vector<int>> d = bfs(buttons[i].first, buttons[i].second, maze);
            dd[i] = d;
            // 从某个点到终点不需要拿石头
            dist[i][nb + 1] = d[tx][ty];
        }

        for (int i = 0; i < nb; i++) {
            int tmp = -1;
            for (int k = 0; k < ns; k++) {
                int mid_x = stones[k].first, mid_y = stones[k].second;
                if (dd[i][mid_x][mid_y] != -1 && start_dist[mid_x][mid_y] != -1) {
                    if (tmp == -1 || tmp > dd[i][mid_x][mid_y] + start_dist[mid_x][mid_y]) {
                        tmp = dd[i][mid_x][mid_y] + start_dist[mid_x][mid_y];
                    }
                }
            }
            dist[i][nb] = tmp;
            for (int j = i + 1; j < nb; j++) {
                int mn = -1;
                for (int k = 0; k < ns; k++) {
                    int mid_x = stones[k].first, mid_y = stones[k].second;
                    if (dd[i][mid_x][mid_y] != -1 && dd[j][mid_x][mid_y] != -1) {
                        if (mn == -1 || mn > dd[i][mid_x][mid_y] + dd[j][mid_x][mid_y]) {
                            mn = dd[i][mid_x][mid_y] + dd[j][mid_x][mid_y];
                        }
                    }
                }
                dist[i][j] = mn;
                dist[j][i] = mn;
            }
        }

        // 无法达成的情形
        for (int i = 0; i < nb; i++) {
            if (dist[i][nb] == -1 || dist[i][nb + 1] == -1) return -1;
        }

        // dp 数组， -1 代表没有遍历到
        vector<vector<int>> dp(1 << nb, vector<int>(nb, -1));
        for (int i = 0; i < nb; i++) {
            dp[1 << i][i] = dist[i][nb];
        }

        // 由于更新的状态都比未更新的大，所以直接从小到大遍历即可
        for (int mask = 1; mask < (1 << nb); mask++) {
            for (int i = 0; i < nb; i++) {
                // 当前 dp 是合法的
                if (mask & (1 << i)) {
                    for (int j = 0; j < nb; j++) {
                        // j 不在 mask 里
                        if (!(mask & (1 << j))) {
                            int next = mask | (1 << j);
                            if (dp[next][j] == -1 || dp[next][j] > dp[mask][i] + dist[i][j]) {
                                dp[next][j] = dp[mask][i] + dist[i][j];
                            }
                        }
                    }
                }
            }
        }

        int ret = -1;
        int final_mask = (1 << nb) - 1;
        for (int i = 0; i < nb; i++) {
            if (ret == -1 || ret > dp[final_mask][i] + dist[i][nb + 1]) {
                ret = dp[final_mask][i] + dist[i][nb + 1];
            }
        }

        return ret;
    }
};