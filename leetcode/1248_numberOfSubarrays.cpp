// @File   : 1248_numberOfSubarrays.cpp
// @Source : https://leetcode-cn.com/problems/count-number-of-nice-subarrays/
// @Title  : 1248. 统计「优美子数组」
// @Auther : sun_ds
// @Date   : 2020/4/21

/**  题目描述：
    给你一个整数数组 nums 和一个整数 k。

    如果某个 连续 子数组中恰好有 k 个奇数数字，我们就认为这个子数组是「优美子数组」。

    请返回这个数组中「优美子数组」的数目。

     

    示例 1：

    输入：nums = [1,1,2,1,1], k = 3
    输出：2
    解释：包含 3 个奇数的子数组是 [1,1,2,1] 和 [1,2,1,1] 。
    示例 2：

    输入：nums = [2,4,6], k = 1
    输出：0
    解释：数列中不包含任何奇数，所以不存在优美子数组。
    示例 3：

    输入：nums = [2,2,2,1,2,2,1,2,2,2], k = 2
    输出：16
     

    提示：

    1 <= nums.length <= 50000
    1 <= nums[i] <= 10^5
    1 <= k <= nums.length


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/count-number-of-nice-subarrays
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.滑动窗口 中心扩散
 * 使用order记录nums中各个奇数的位置(索引)
 * 要求满足窗口内k个奇数。即起始奇数为order[i],则结束奇数为order[i+k-1].
 * 则包含[i~i+k-1]之间奇数的子数组个数为 (order[i] - order[i-1])*(order[i+k] - order[i+k-1])
 * order[i]前面的偶数个数为order[i] - order[i-1] - 1; 算上order[i]本身，前面一共order[i] - order[i-1]种选择
 * order[i+k-1]后面的偶数个数为order[i+k] - order[i+k-1] - 1; 算上order[i+k-1]本身，后面一共order[i+k] - order[i+k-1]种选择
 *
 * 为了方便处理边界，在前后加上虚节点。-1和nums.size()；
 *
 * 时间复杂度O(n)
 *
 *
 * 2.前缀和-差分 每个位置计算
 *
 * 前缀和count统计当前位置前出现的奇数个数。索引为位置，值为当前位置之前(包括当前)的奇数个数
 * 遍历count[i] - count[j-1]为区间[j,i]之间奇数个数。
 * 遍历i，j得到结果。
 * 时间复杂度O(n)
 *
 * 使用count统计，索引为当前位置前奇数的个数，值为这样位置的个数。
 * 使用i遍历nums各个位置，一直用sum统计奇数的个数。并存入count[sum]++;
 * 每个以i结尾，且满足子数组中包含k个奇数的个数为count[sum-k]
 * 当前位置前奇数个数为sum，所以找有几个位置前是sum-k个奇数
 * 这样这几个位置都能够作为起点，i作为终点，满足子数组包含k个奇数。
 *
 * 由于遍历的顺序，count[sum-k]的值，已经由前面更新固定了。
 *
 * 起始值count[0] = 1;
 * cnt[0] = 1;// 考虑k个奇数。此时需要补充个cnt[0]=1.
 *
 * 时间复杂度O(n)
 *
 *
 *
 */


//滑动窗口
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        vector<int> order;
        //记录奇数位置
        order.push_back(-1); //虚节点
        for(int i=0;i<nums.size();i++){
            if(nums[i]&1) order.push_back(i);
        }
        order.push_back(nums.size()); //虚节点
        int res = 0;
        //滑动窗口 窗口大小k+1. i~i+k+1
        for(int i=0;i+k+1<order.size();i++){
            int front = order[i+1] - order[i];
            int back = order[i+k+1] - order[i+k];
            //前面可选*后面可选
            res += front*back;
        }
        return res;
    }
};


//前缀和差分
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> cnt(n+1,0);
        int sum=0;
        int res = 0;
        cnt[0] = 1;// 考虑k个奇数。此时需要补充个cnt[0]=1.
        for(int i=0;i<n;i++){
            //当前位置前出现的奇数个数
            sum += nums[i]&1;
            cnt[sum]++;
            res += sum-k >= 0 ? cnt[sum-k] : 0;
        }
        return res;
    }
};
