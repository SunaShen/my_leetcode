// @File   : 416_canPartition.cpp
// @Source : https://leetcode-cn.com/problems/partition-equal-subset-sum/
// @Title  : 416. 分割等和子集
// @Auther : sun_ds
// @Date   : 2020/10/11

/**  题目描述：
    给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

    注意:

    每个数组中的元素不会超过 100
    数组的大小不会超过 200
    示例 1:

    输入: [1, 5, 11, 5]

    输出: true

    解释: 数组可以分割成 [1, 5, 5] 和 [11].
     

    示例 2:

    输入: [1, 2, 3, 5]

    输出: false

    解释: 数组不能分割成两个元素和相等的子集.

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/partition-equal-subset-sum
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 数组之和为 sum，易知，若 sum 为奇数必定返回 false。
 * 转换成背包问题。选取数组中的各个元素组成 target = sum / 2
 * 该背包问题要求背包必须刚好填满。因此动态规划时只有两种状态 true 和 false
 * dp[n][target + 1]
 * dp[i][j] 表示前 i 个元素能否组成和为 j, true 为可以，false 为不可以
 *
 * 初始条件:
 * 当 j == 0 时，全部不选即可，肯定能满足
 *  所以所有的 dp[i][0] = true;
 * 当 i == 0 时，需要判断 nums[i] 是否等于 j
 *  若 nums[i] == j dp[0][nums[i]] = true;
 *
 * 状态转移方程:
 *  1) 不选择 nums[i] 时 dp[i][j] = dp[i-1][j]
 *  2) 选择 nums[i] 并且满足 j-nums[i]>=0 时 dp[i][j] = dp[i-1][j-nums[i]]
 *
 * 最终结果为 dp[n][target]
 *
 * 时间复杂度 O(N*target)
 * 空间复杂度 O(N*target) 使用滚动数组 O(target)
 *
 *
 */

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        if(nums.size() == 0) return false;
        int sum=0;
        for(auto i:nums) sum += i;
        if(sum % 2 != 0) return false;
        int target = sum / 2;
        int n = nums.size();
        vector<vector<bool>> dp(n, vector<bool>(target+1, false));
        for(int i=0;i<n;i++){
            dp[i][0] = true;
        }
        if(nums[0] <= target){
            dp[0][nums[0]] = true;
        }
        for(int i=1;i<n;i++){
            for(int j=0;j<=target;j++){
                if(nums[i] <= j){
                    dp[i][j] = dp[i-1][j] || dp[i-1][j - nums[i]];
                }else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[n-1][target];
    }
};

// 滚动数组
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        if(nums.size() == 0) return false;
        int sum=0;
        for(auto i:nums) sum += i;
        if(sum % 2 != 0) return false;
        int target = sum / 2;
        int n = nums.size();
        vector<bool> dp(target+1, false);
        dp[0] = true;
        if(nums[0] <= target){
            dp[nums[0]] = true;
        }
        for(int i=1;i<n;i++){
            // 逆序 防止影响 dp[j - nums[i]]
            for(int j=target;j>=nums[i];j--){
                dp[j] = dp[j] || dp[j - nums[i]];
            }
        }
        return dp[target];
    }
};