// @File   : 312_maxCoins.cpp
// @Source : https://leetcode-cn.com/problems/burst-balloons/
// @Title  : 312. 戳气球
// @Auther : sun_ds
// @Date   : 2020/7/19

/**  题目描述：
    有 n 个气球，编号为0 到 n-1，每个气球上都标有一个数字，这些数字存在数组 nums 中。

    现在要求你戳破所有的气球。如果你戳破气球 i ，就可以获得 nums[left] * nums[i] * nums[right] 个硬币。 这里的 left 和 right 代表和 i 相邻的两个气球的序号。注意当你戳破了气球 i 后，气球 left 和气球 right 就变成了相邻的气球。

    求所能获得硬币的最大数量。

    说明:

    你可以假设 nums[-1] = nums[n] = 1，但注意它们不是真实存在的所以并不能被戳破。
    0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
    示例:

    输入: [3,1,5,8]
    输出: 167
    解释: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
         coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/burst-balloons
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dp 开区间
 *  dp[i][j]表示区间(i,j)之间气球依次戳破后得到的硬币最大值。
 *  注意 dp[i][j] 表示的是开区间。即得到的金币最大值只是[i+1,j-1]之间气球戳破得到的硬币最大值，此时还剩 i 和 j 的气球呢。
 *
 *  转移方程：
 *  dp[i][j] = max(dp[i][k] + temp[i]*temp[k]*temp[j] + dp[k][j]); k = (i,j)
 *
 *  其中 k 表示区间(i,j)中最后一个被戳破的气球。此时的状况是，只有气球 i，k ，j。他们三者结合是 temp[i]*temp[k]*temp[j]
 *  除此之外，还要加上之前戳破的硬币。即区间 (i,k) 和 (k,j) 之间的硬币，即 dp[i][k],dp[k][j]
 *
 *  其中，对于 dp[i][j].只有 i<j 才有意义。
 *  将 dp 看成二维矩阵，左下都没有意义为 0；
 *  每次 dp[i][j] 更新需要 dp[i][k],dp[k][j],k = (i,j).
 *  即当前位置需要其 左边 和 下边的值。因此，从右下角开始更新。
 *  对于 i 从大到小，对于 j 从小到大。
 *
 *  最终得到右上角值为结果。
 *
 *
 *  本题精髓。开区间。
 *  即得到 将（i，j）从 k 拆开之后会剩下 i，k，j。
 *  因为是开区间，所以前面肯定剩下 i，后面肯定剩下 j，这对状态转移很重要。
 *
 */


class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> temp(n+2);
        vector<vector<int>> dp(n+2,vector<int>(n+2,0));
        for(int i=1;i<=n;i++){
            temp[i] = nums[i-1];
        }
        temp[0] = temp[n+1] = 1;
        for(int i=n-1;i>=0;i--){
            for(int j=i+2;j<n+2;j++){
                for(int k=i+1;k<j;k++){
                    int sum = dp[i][k] + dp[k][j] + temp[i]*temp[k]*temp[j];
                    dp[i][j] = max(dp[i][j], sum);
                }
            }
        }
        return dp[0][n+1];
    }
};