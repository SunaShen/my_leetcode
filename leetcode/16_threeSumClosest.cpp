// @File   : 16_threeSumClosest.cpp
// @Source : https://leetcode-cn.com/problems/3sum-closest/
// @Title  : 16. 最接近的三数之和
// @Auther : sun_ds
// @Date   : 2020/6/24

/**  题目描述：
    给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。

     

    示例：

    输入：nums = [-1,2,1,-4], target = 1
    输出：2
    解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2) 。
     

    提示：

    3 <= nums.length <= 10^3
    -10^3 <= nums[i] <= 10^3
    -10^4 <= target <= 10^4


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/3sum-closest
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 排序 + 双指针
 *
 */

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int res = 1e5;
        for(int i=0;i<n;i++){
            int j = i+1, k = n-1;
            while(j<k){
                if (nums[j]+nums[k] == target - nums[i]) {
                    return target;
                } else if (nums[j]+nums[k] < target - nums[i]){
                    if(abs(target - nums[i] - nums[j] - nums[k]) < abs(target - res)){
                        res = nums[i] + nums[j] + nums[k];
                    }
                    j++;
                } else {
                    if(abs(target - nums[i] - nums[j] - nums[k]) < abs(target - res)){
                        res = nums[i] + nums[j] + nums[k];
                    }
                    k--;
                }
            }
        }
        return res;
    }
};



class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int res = 1e5;
        for(int i=0;i<n;i++){
            //跳过重复元素
            if(i>0 && nums[i] == nums[i-1]) continue;
            int j = i+1, k = n-1;
            while(j<k){
                if (nums[j]+nums[k] == target - nums[i]) {
                    return target;
                } else if (nums[j]+nums[k] < target - nums[i]){
                    if(abs(target - nums[i] - nums[j] - nums[k]) < abs(target - res)){
                        res = nums[i] + nums[j] + nums[k];
                    }
                    //跳过重复元素
                    int j0 = j;
                    while(j0 < k && nums[j0] == nums[j]) j0++;
                    j = j0;
                } else {
                    if(abs(target - nums[i] - nums[j] - nums[k]) < abs(target - res)){
                        res = nums[i] + nums[j] + nums[k];
                    }
                    //跳过重复元素
                    int k0 = k;
                    while(j < k0 && nums[k0] == nums[k]) k0--;
                    k = k0;
                }
            }
        }
        return res;
    }
};


