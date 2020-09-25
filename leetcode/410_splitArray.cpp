// @File   : 410_splitArray.cpp
// @Source : https://leetcode-cn.com/problems/split-array-largest-sum/
// @Title  : 410. 分割数组的最大值
// @Auther : sun_ds
// @Date   : 2020/7/25

/**  题目描述：
    给定一个非负整数数组和一个整数 m，你需要将这个数组分成 m 个非空的连续子数组。设计一个算法使得这 m 个子数组各自和的最大值最小。

    注意:
    数组长度 n 满足以下条件:

    1 ≤ n ≤ 1000
    1 ≤ m ≤ min(50, n)
    示例:

    输入:
    nums = [7,2,5,10,8]
    m = 2

    输出:
    18

    解释:
    一共有四种方法将nums分割为2个子数组。
    其中最好的方式是将其分为[7,2,5] 和 [10,8]，
    因为此时这两个子数组各自的和的最大值为18，在所有情况中最小。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/split-array-largest-sum
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1.dp+前缀和
 * dp[i][j]表示前 i 个数分为 j 个子数组后，最大连续子数组和的最小值。
 * 考虑第 j 段的取值范围，枚举 k，其中前 k 个数被分为 j-1 段，而第 k+1 至 i 为第 j 段。
 * 遍历 k，则此时，转移方程为：
 * dp[i][j] = min( max(dp[k][j-1], sub(k+1,i)) ); 其中k = [0,i-1]。
 * 其中sub(k+1,i)表示[k+1,i] 区间的和。使用前缀和来计算。
 *
 * 由于 dp[i][j] 的特性，必须满足 i<=j. 因此，对于 i>j 的 dp[i][j] 置无效值。目标是 dp 取最小，所以无效值使用 INT_MAX。
 *
 * 考虑初值：
 * 在上述的状态转移方程中，当 j=1 时，唯一的可能性就是前 i 个数被分成了一段。
 * 如果枚举的 k=0，那么就代表着这种情况；
 * 如果 k!=0，对应的状态 dp[k][0] 是一个不合法的状态，无法进行转移。
 * 因此我们需要令 dp[0][0]=0。
 *
 * 最终结果为 dp[n][m]
 *
 * 时间复杂度 O(N^2*M)
 * 空间复杂度 O(N*M)
 *
 * 2.二分法
 * 二分法搜索整个取值空间。
 * 结果肯定在 nums 的最大值与它的总和之间。
 * 搜索范围，l = Max, r = Sum;
 * 假设知道了每个子数组的最大值为 mid。
 * 则，遍历数组 nums，看能否在每个子数组和不大于 mid 的情况下分到 m 段以内。
 * 若 分段数小于 m 说明还有优化空间，r=mid。否则，说明子数组的和不太够，增大，l=mid+1.
 * 二分法，最终找到合适的值。
 *
 * 逆向思维，从结果出发。
 *
 * 时间复杂度 O(N*log(Sum - Max))
 * 其中 N 为数组长度，Sum 为数组的和，Max 为数组中最大值。
 * 空间复杂度 O(1)
 *
 */

class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        vector<vector<long long>> dp(n+1, vector<long long>(m+1, INT_MAX));
        vector<long long> sum(n+1,0); //前缀和
        for(int i=0;i<n;++i){
            sum[i+1] = sum[i] + nums[i];
        }
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j<=min(i,m); ++j){
                for(int k=0;k<i;++k){
                    dp[i][j] = min(dp[i][j], max(dp[k][j-1], sum[i] - sum[k]));
                }
            }
        }
        return dp[n][m];
    }
};

class Solution {
public:
    bool check(vector<int>& nums, int x, int m) {
        long long sum = 0;
        int cnt = 1;
        // 分组，每个组都不能大于 x
        for (auto i : nums) {
            if (sum + i > x) {
                // 新起一个分组
                ++cnt;
                sum = i;
            } else {
                sum += i;
            }
        }
        // 满足cnt <= m说明还有压缩空间
        return cnt <= m;
    }
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size();
        int Max = 0;
        long long Sum = 0;
        for (auto i : nums) {
            Max = max(Max,i);
            Sum += i;
        }
        // 搜索范围
        long long l = Max, r = Sum;
        while (l < r) {
            int mid = l + ((r-l)>>1);
            if (check(nums, mid, m)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
};

