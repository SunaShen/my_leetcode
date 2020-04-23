// @File   : 560_subarraySum.cpp
// @Source : https://leetcode-cn.com/problems/subarray-sum-equals-k/
// @Title  : 560. 和为K的子数组
// @Auther : sun_ds
// @Date   : 2020/4/23

/**  题目描述：
    给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。

    示例 1 :

    输入:nums = [1,1,1], k = 2
    输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。
    说明 :

    数组的长度为 [1, 20,000]。
    数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]。


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/subarray-sum-equals-k
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 1.前缀和
 * 构建前缀和数组sum
 * 则区间[i,j]的子数组和为 sum[j] - sum[i-1]
 * 遍历子数组开始和结束的位置。判断子数组和sum[j] - sum[i-1]是否等于k，等于k就统计加一。
 * 时间复杂度O(N^2)
 * 空间复杂度O(N)
 *
 * 2.遍历
 * 两层循环遍历起始和结束位置
 * 使用sum统计以固定起点i开头的子数组和。
 * 若sum==k，计数加一。
 * 时间复杂度O(N^2)
 * 空间复杂度O(1)
 *
 * 3.哈希表
 * 借助前缀和原理，有公式 sum[j] - sum[i-1] == k 时，计数加一。
 * 变形为，sum[j] - k == sum[i-1];
 * 使用map，前缀和为map的索引，值为出现的次数。
 * 当以j结尾时，计算sum[j] - k是否在map中，若是在就计数加上map[sum[j] - k]；
 *
 * 空间换时间
 * 时间复杂度O(N)
 * 空间复杂度O(N)
 *
 *
 */
//前缀和 遍历
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> sum(n+1,0);//前缀和
        for(int i=0;i<n;i++){
            sum[i+1] = sum[i] + nums[i];
        }
        int res = 0;
        for(int i=1;i<=n;i++){
            for(int j=i;j<=n;j++){
                if(sum[j] - sum[i-1]==k){
                    res++;
                }
            }
        }
        return res;
    }
};
//遍历
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int res = 0;
        for(int i=0;i<n;i++){
            int sum = 0;
            for(int j=i;j<n;j++){
                sum += nums[j];
                if(sum==k) res++;
            }
        }
        return res;
    }
};
//哈希
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int res = 0;
        unordered_map<int,int> m;
        m[0] = 1;//考虑数组中只有一个k
        int sum = 0;
        for(int i=0;i<n;i++){
            sum += nums[i];
            if(m.count(sum-k)){
                res += m[sum-k];
            }
            m[sum]++;
        }
        return res;
    }
};
