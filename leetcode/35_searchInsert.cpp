// @File   : 35_searchInsert.cpp
// @Source : https://leetcode-cn.com/problems/search-insert-position/
// @Title  : 35. 搜索插入位置
// @Auther : sun_ds
// @Date   : 2020/7/17

/**  题目描述：
    给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

    你可以假设数组中无重复元素。

    示例 1:

    输入: [1,3,5,6], 5
    输出: 2
    示例 2:

    输入: [1,3,5,6], 2
    输出: 1
    示例 3:

    输入: [1,3,5,6], 7
    输出: 4
    示例 4:

    输入: [1,3,5,6], 0
    输出: 0

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/search-insert-position
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 1.二分法
 * 找到第一个大于等于 target 的位置。
 *
 */

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int l = 0, r = n-1;
        while(l <= r){
            int mid = l + ((r - l)>>1);
            if(nums[mid] < target){
                l = mid + 1;
            }else{
                r = mid - 1;
            }
        }
        return l;
    }
};

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        auto iter = std::lower_bound(nums.begin(),nums.end(),target);
        return iter - nums.begin();
    }
};

