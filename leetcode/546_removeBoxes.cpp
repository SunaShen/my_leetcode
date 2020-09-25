// @File   : 546_removeBoxes.cpp
// @Source : https://leetcode-cn.com/problems/remove-boxes/
// @Title  : 546. 移除盒子
// @Auther : sun_ds
// @Date   : 2020/8/15

/**  题目描述：
    给出一些不同颜色的盒子，盒子的颜色由数字表示，即不同的数字表示不同的颜色。
    你将经过若干轮操作去去掉盒子，直到所有的盒子都去掉为止。每一轮你可以移除具有相同颜色的连续 k 个盒子（k >= 1），这样一轮之后你将得到 k*k 个积分。
    当你将所有盒子都去掉之后，求你能获得的最大积分和。

     

    示例：

    输入：boxes = [1,3,2,2,2,3,4,3,1]
    输出：23
    解释：
    [1, 3, 2, 2, 2, 3, 4, 3, 1]
    ----> [1, 3, 3, 4, 3, 1] (3*3=9 分)
    ----> [1, 3, 3, 3, 1] (1*1=1 分)
    ----> [1, 1] (3*3=9 分)
    ----> [] (2*2=4 分)
     

    提示：

    1 <= boxes.length <= 100
    1 <= boxes[i] <= 100

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/remove-boxes
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1. dp
 *
 *  传统思维 设置 dp[l][r] 为消去 区间[l,r]的最大积分。无法写出转移方程。
 *  我们并不能直接使用起始节点和结束节点决定最大分数，因为这个分数并不只依赖于子序列，也依赖于之前的移动对当前数组的影响，这可能让最终的子序列不是一个连续的子串。
 *  比如 {3,4,2,4,4}，如果先把 2 移除，3 个 4 会合并在一起，对答案的贡献是 3^2 = 9
 *  如果先移除左右两边的 4 再移除 2 这里 3 个 4 的贡献就是 1^2 + 2^2 = 5，最优的办法当然是先取走 2，但是这样剩下的 3 个 4 其实并不是原串的某个连续子串。
 *
 *
 *  设 dp[l][r][k] 表示移除 {区间[l，r]的元素 + 该区间右边等于 ar 的 k 个元素} 所组成的这个序列的最大积分。
 *  为什么后面会有 k 个连续的与 ar 相等的元素？。其实不一定有，但是假设无关元素都已经被前面步骤消除，那么在这个假设下就有。
 *  每次有两种策略。
 *  1）先将 ar 和后面阈值相等的 k 个元素组成的区间移除，则剩下区间 [l, r-1]. 得分为 dp[l][r-1][0] + (k+1)^2
 *      dp[l][r-1][0] 中 k=0 的原因是 ar 后面都被消完了，也就没有元素等于 a_{r-1} 了。
 *  2）先消除[l,r]中间的某个区间，然后再计算。那么此时 ar 只能归类为后面 k 个元素的其中一员，变为 k+1 个元素。
 *   这样要想借助之前的 dp，那么 需要的区间的最后一位也必须等于 ar 啊。
 *   因此，遍历 l~r-1 ，找到等于 ar 的元素ai，使它作为分隔符，先消掉 [i+1,r-1] 区间，然后升下的情况为 [l,i] 且后面有 k+1 个元素与 ai 相等。
 *    当前积分为 dp[l][i][k+1] + dp[i+1][r-1][0], 由于 i 不确定，所以只能遍历
 *
 *   因此，转移方程为
 *    dp[l][r][k] = max(dp[l][r-1][0] + (k+1)^2 +
 *                      max(dp[l][i][k+1] + dp[i+1][r-1][0])) 其中 i = [l, r-1] 并且 ai == ar
 *
 *
 * 时间复杂度 O(N^4)
 * 空间复杂度 O(N^3)
 *
 */

class Solution {
public:
    int dp[100][100][100];

    int removeBoxes(vector<int>& boxes) {
        memset(dp, 0, sizeof dp);
        return calculatePoints(boxes, 0, boxes.size() - 1, 0);
    }

    int calculatePoints(vector<int>& boxes, int l, int r, int k) {
        if (l > r) return 0;
        if (dp[l][r][k] != 0) return dp[l][r][k];

        // 优化 若 ar 前面有和 ar 相等的，则优先合并
        // 这样使得 r 更小，后序遍历时搜索区间更小。达到优化效果
        while (r > l && boxes[r] == boxes[r - 1]) {
            r--;
            k++;
        }

        dp[l][r][k] = calculatePoints(boxes, l, r - 1, 0) + (k + 1) * (k + 1);
        for (int i = l; i < r; i++) {
            if (boxes[i] == boxes[r]) {
                dp[l][r][k] = max(dp[l][r][k], calculatePoints(boxes, l, i, k + 1) +
                                               calculatePoints(boxes, i + 1, r - 1, 0));
            }
        }
        return dp[l][r][k];
    }
};

// 非递归版(C++会超时..)
class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n+1, 0)));
        for(int len = 1; len <= n; len++){
            for(int i = 0; i + len - 1 < n; i++){
                int j = i + len - 1;
                for(int k = 0; k < n; k++){
                    dp[i][j][k] = max(dp[i][j][k], (j - 1 < i ? 0: dp[i][j - 1][0]) + (k + 1) * (k + 1));
                    for(int t = i; t <= j - 1; t++){
                        if(boxes[t] == boxes[j]){
                            dp[i][j][k] = max(dp[i][j][k], (t + 1 > j - 1 ? 0: dp[t + 1][j - 1][0]) +
                                                           dp[i][t][k + 1]);
                        }
                    }
                }
            }
        }
        return dp[0][n - 1][0];
    }
};