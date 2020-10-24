// @File   : 1024_videoStitching.cpp
// @Source : https://leetcode-cn.com/problems/video-stitching/
// @Title  : 1024. 视频拼接
// @Auther : sun_ds
// @Date   : 2020/10/24

/**  题目描述：
    你将会获得一系列视频片段，这些片段来自于一项持续时长为 T 秒的体育赛事。这些片段可能有所重叠，也可能长度不一。

    视频片段 clips[i] 都用区间进行表示：开始于 clips[i][0] 并于 clips[i][1] 结束。我们甚至可以对这些片段自由地再剪辑，例如片段 [0, 7] 可以剪切成 [0, 1] + [1, 3] + [3, 7] 三部分。

    我们需要将这些片段进行再剪辑，并将剪辑后的内容拼接成覆盖整个运动过程的片段（[0, T]）。返回所需片段的最小数目，如果无法完成该任务，则返回 -1 。

     

    示例 1：

    输入：clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], T = 10
    输出：3
    解释：
    我们选中 [0,2], [8,10], [1,9] 这三个片段。
    然后，按下面的方案重制比赛片段：
    将 [1,9] 再剪辑为 [1,2] + [2,8] + [8,9] 。
    现在我们手上有 [0,2] + [2,8] + [8,10]，而这些涵盖了整场比赛 [0, 10]。
    示例 2：

    输入：clips = [[0,1],[1,2]], T = 5
    输出：-1
    解释：
    我们无法只用 [0,1] 和 [1,2] 覆盖 [0,5] 的整个过程。
    示例 3：

    输入：clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], T = 9
    输出：3
    解释：
    我们选取片段 [0,4], [4,7] 和 [6,9] 。
    示例 4：

    输入：clips = [[0,4],[2,8]], T = 5
    输出：2
    解释：
    注意，你可能录制超过比赛结束时间的视频。
     

    提示：

    1 <= clips.length <= 100
    0 <= clips[i][0] <= clips[i][1] <= 100
    0 <= T <= 100


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/video-stitching
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dp
 *  dp[i] 表示区间 [0,i) 所需的最少区间的数量。
 *  枚举每个子区间 {clips[j][0] - clips[j][1]}
 *  若满足 clips[j][0] < i <= clips[j][1]
 *    那么该子区间就可以覆盖 [0,i) 的后半部分,而前半部分由 dp[clips[j][0]] 得到。
 *    即转移方程 为 dp[i] = min(dp[clips[j][0]]) + 1
 *
 *  最终结果为 dp[T]
 *
 *  时间复杂度 O(T*N)
 *  空间复杂度 O(T)
 *
 * 2.贪心
 * 注意到对于所有左端点相同的子区间，其右端点越远越有利。且最佳方案中不可能出现两个左端点相同的子区间。
 *
 * 于是我们预处理所有的子区间，对于每一个位置 i，我们记录以其为左端点的子区间中最远的右端点，记为 maxn[i]。
 *
 * 我们可以参考「55. 跳跃游戏的官方题解」，使用贪心解决这道题。
 *
 * 具体地，我们枚举每一个位置，假设当枚举到位置 i 时，记左端点不大于 i 的所有子区间的最远右端点为 last。这样 last 就代表了当前能覆盖到的最远的右端点。
 *
 * 每次我们枚举到一个新位置，我们都用 maxn[i] 来更新 last。如果更新后 last==i，那么说明下一个位置无法被覆盖，我们无法完成目标。
 *
 * 同时我们还需要记录上一个被使用的子区间的结束位置为 pre，每次我们越过一个被使用的子区间，就说明我们要启用一个新子区间，这个新子区间的结束位置即为当前的 last。也就是说，每次我们遇到 i==pre，则说明我们用完了一个被使用的子区间。这种情况下我们让答案加 1，并更新 pre 即可。
 *
 * 作者：LeetCode-Solution
 * 链接：https://leetcode-cn.com/problems/video-stitching/solution/shi-pin-pin-jie-by-leetcode-solution/
 * 来源：力扣（LeetCode）
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 *
 */

class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        vector<int> dp(T + 1, INT_MAX - 1);
        dp[0] = 0;
        for(int i = 1; i <= T; i++){
            for(int j = 0; j < clips.size(); j++){
                if(clips[j][0] < i && i <= clips[j][1]){
                    dp[i] = min(dp[i], dp[clips[j][0]] + 1);
                }
            }
        }
        return dp[T] == INT_MAX - 1 ? -1 : dp[T];
    }
};


class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        vector<int> maxn(T);
        int last = 0, ret = 0, pre = 0;
        for (vector<int>& it : clips) {
            if (it[0] < T) {
                maxn[it[0]] = max(maxn[it[0]], it[1]);
            }
        }
        for (int i = 0; i < T; i++) {
            last = max(last, maxn[i]);
            if (i == last) {
                return -1;
            }
            if (i == pre) {
                ret++;
                pre = last;
            }
        }
        return ret;
    }
};
