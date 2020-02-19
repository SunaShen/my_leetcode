// @File   : 1349_maxStudents.cpp
// @Source : https://leetcode-cn.com/problems/maximum-students-taking-exam/
// @Title  : 参加考试的最大学生数
// @Auther : sun_ds
// @Date   : 2020/2/17

/**  题目描述：
    给你一个 m * n 的矩阵 seats 表示教室中的座位分布。如果座位是坏的（不可用），就用 '#' 表示；否则，用 '.' 表示。

    学生可以看到左侧、右侧、左上、右上这四个方向上紧邻他的学生的答卷，但是看不到直接坐在他前面或者后面的学生的答卷。请你计算并返回该考场可以容纳的一起参加考试且无法作弊的最大学生人数。

    学生必须坐在状况良好的座位上。

     

    示例 1：



    输入：seats = [["#",".","#","#",".","#"],
                  [".","#","#","#","#","."],
                  ["#",".","#","#",".","#"]]
    输出：4
    解释：教师可以让 4 个学生坐在可用的座位上，这样他们就无法在考试中作弊。
    示例 2：

    输入：seats = [[".","#"],
                  ["#","#"],
                  ["#","."],
                  ["#","#"],
                  [".","#"]]
    输出：3
    解释：让所有学生坐在可用的座位上。
    示例 3：

    输入：seats = [["#",".",".",".","#"],
                  [".","#",".","#","."],
                  [".",".","#",".","."],
                  [".","#",".","#","."],
                  ["#",".",".",".","#"]]
    输出：10
    解释：让学生坐在第 1、3 和 5 列的可用座位上。
     

    提示：

    seats 只包含字符 '.' 和'#'
    m == seats.length
    n == seats[i].length
    1 <= m <= 8
    1 <= n <= 8


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/maximum-students-taking-exam
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 状态压缩 dp
 *
 *    1 <= m <= 8
 *    1 <= n <= 8
 * 因此可以将每一行座位状态(是否坐人)，压缩成一个8位的数字。
 * 因此每一行共有1<<m中组合的可能。
 *
 * 所以定义dp[n+1][1<<m]。 创建dp[0]为初始状态。
 * dp[i][bits] 表示前i行中，第i行坐人情况为bits的情况下，最多的人数。
 *
 * 当前行是否能坐人与几个情况有关，
 * 1.首先判断当前行的当前位置，bits是否表示有人
 * 2.判断当前位置是否作为是'.',而不是'#'。
 * 3.判断当前左右是否有人  cur行
 * 4.判断当前的前一行左右是否有人 pre行    也需要判断上一行的pre是否存在 是否为-1
 *
 * 若都满足条件，则更新，dp   dp[i][cur] = max(dp[i][cur], dp[i-1][pre] + bcount(cur))
 * 其中bcount(cur)表示，当前i行的坐人情况的值cur中包含1的个数，即当前行坐人的个数。
 *
 * 更新各状态。
 * 最终取第n行的各个坐人状态，找到一个最大的即为返回值。
 *
 *
 *
 * 使用状态压缩，将一行坐人状态压成一个数。
 * 当前能否坐人只与当前行cur和前一行pre有关。
 * 遍历各个pre和cur状态。
 * 从前往后，直到最后一行n。
 * 从第n行中的各做人状态cur中选出最大的坐人数。
 *
 *
 *
 */


class Solution {
public:
    int dp[10][1<<8];
    //取低位
    int lowbit(int x){
        return x&-x;
    }
    int bcount(int x){
        int ret = 0;
        while(x > 0){
            ++ret;
            x -= lowbit(x);
        }
        return ret;
    }
    int maxStudents(vector<vector<char>>& seats) {
        int n = seats.size(), m = seats[0].size();

        memset(dp,-1,sizeof(dp));
        dp[0][0] = 0;

        int lim = (1<<m);
        for(int i = 1; i <= n; i++){
            for(int cur = 0; cur < lim; cur++){
                for(int pre = 0; pre < lim; pre++){
                    if(dp[i-1][pre] == -1) continue;

                    bool flag = true;
                    for(int j = 0; j < m; j++){
                        if(((cur>>j)&1)==0) continue;
                        if(seats[i-1][j] == '#') flag = false;
                        if(j >= 1 && ((cur>>(j-1))&1)) flag = false;
                        if(j+1 < m && ((cur>>(j+1))&1)) flag = false;
                        if(j >= 1 && ((pre>>(j-1))&1)) flag = false;
                        if(j+1 < m && ((pre>>(j+1))&1)) flag = false;
                    }
                    if(!flag) continue;
                    dp[i][cur] = max(dp[i][cur], dp[i-1][pre] + bcount(cur));
                }
            }
        }
        int ans = 0;
        for(int s = 0; s < lim; s++) ans = max(ans, dp[n][s]);
        return ans;
    }
};
