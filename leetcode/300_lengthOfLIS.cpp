// @File   : 300_lengthOfLIS.cpp
// @Source : https://leetcode-cn.com/problems/longest-increasing-subsequence/
// @Title  : 最长上升子序列
// @Auther : sun_ds
// @Date   : 2019/11/13

/*  题目描述：
    给定一个无序的整数数组，找到其中最长上升子序列的长度。

    示例:

    输入: [10,9,2,5,3,7,101,18]
    输出: 4
    解释: 最长的上升子序列是 [2,3,7,101]，它的长度是 4。
    说明:

    可能会有多种最长上升子序列的组合，你只需要输出对应的长度即可。
    你算法的时间复杂度应该为 O(n2) 。
    进阶: 你能将算法的时间复杂度降低到 O(n log n) 吗?

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/longest-increasing-subsequence
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 *
 * 给定一个无序的整数数组，找到其中最长上升子序列的长度。
 *
 * 动态规划
 *
 * 两种方法:
 * 1.dp[i]存储的是，当nums[i]元素为结尾时递增序列的最长长度
 *  nums[i] <= nums[j]时 跳过j
 *  nums[i] > nums[j]时 dp[i] = max(dp[i],dp[j]+1)
 *  最终max(dp)得结果
 *  复杂度O(n^2)
 * 2.dp[i]存储 实现最短递增序列长度为i的序列的最后一个元素。
 *  nums[i] > dp[max]时 max++ dp[max] = nums[i]
 *  nums[i] <= dp[max]时 nums[i] 替换dp中第一个使得dp[j]>nums[i]成立的dp[j]为nums[i]
 *  上述替换可使用二分法搜索！！！
 *  max即为最终结果
 *  复杂度O(nlog(n))--二分查找
 *
 */



//dp[i]存储的是，当nums[i]元素为结尾时递增序列的最长长度

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if(n==0) return 0;
        vector<int> dp(n,1);
        int ans = -1;
        for(int i=0;i<n;++i){
            int temp = 1;
            for(int j=0;j<i;++j){
                if(nums[i] > nums[j]){
                    temp = max(temp,dp[j]+1);
                }
            }
            dp[i] = temp;
            ans = max(ans,dp[i]);
        }
        return ans;
    }
};

//dp[i]存储 实现最短递增序列长度为i的序列的最后一个元素。
//max存储长度

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if(nums.size()==0)
            return 0;
        vector<int> dp;
        dp.push_back(INT_MIN);
        dp.push_back(nums[0]);
        int max = 1;
        for(int i=1;i<nums.size();++i){
            if(nums[i] > dp[max]){
                max++;
                dp.push_back(nums[i]);
            }else{
                int k = max-1;
                while(k>=0){
                    if(nums[i]>dp[k])
                    {
                        dp[k+1] = nums[i];
                        break;
                    }
                    --k;
                }
            }
        }
        return max;
    }
};

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        vector<int> dp;
        dp.push_back(nums[0]);
        int max = 1;

        for (int i = 1; i < n; i++) {
            if (nums[i] > dp[max - 1]) {
                ++max;
                dp.push_back(nums[i]);
            }else{
                //二分法塞数据
                int l = 0, r = max - 1, mid;
                while (l < r) {
                    mid = (l + r) >> 1;
                    if (dp[mid] < nums[i]) {
                        l = mid + 1;
                    } else {
                        r = mid;
                    }

                }
                if (nums[i] < dp[l]) dp[l] = nums[i];
            }
        }
        return max;
    }
};

