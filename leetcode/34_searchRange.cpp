// @File   : 34_searchRange.cpp
// @Source : https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/
// @Title  : 34. 在排序数组中查找元素的第一个和最后一个位置
// @Auther : sun_ds
// @Date   : 2020/3/30

/**  题目描述：
    给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

    你的算法时间复杂度必须是 O(log n) 级别。

    如果数组中不存在目标值，返回 [-1, -1]。

    示例 1:

    输入: nums = [5,7,7,8,8,10], target = 8
    输出: [3,4]
    示例 2:

    输入: nums = [5,7,7,8,8,10], target = 6
    输出: [-1,-1]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.两次二分法，分别找到起始点和结束点
 * 当起始大于结束表示不存在target
 *
 */


class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l = 0, r = nums.size()-1;
        int start = -1, end = -1;
        while(l<=r){
            int mid = l + ((r - l)>>1);
            if(nums[mid] < target){
                l = mid+1;
            }else{
                r = mid-1;
            }
        }
        start = l;
        l = 0;
        r = nums.size()-1;
        while(l<=r){
            int mid = l + ((r - l)>>1);
            if(nums[mid] <= target){
                l = mid+1;
            }else{
                r = mid-1;
            }
        }
        end = r;
        if(start>end) return {-1,-1};
        return {start,end};
    }
};
