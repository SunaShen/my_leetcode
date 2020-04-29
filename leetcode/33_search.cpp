// @File   : 33_search.cpp
// @Source : https://leetcode-cn.com/problems/search-in-rotated-sorted-array/
// @Title  : 33. 搜索旋转排序数组
// @Auther : sun_ds
// @Date   : 2020/3/31

/**  题目描述：
    假设按照升序排序的数组在预先未知的某个点上进行了旋转。

    ( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

    搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。

    你可以假设数组中不存在重复的元素。

    你的算法时间复杂度必须是 O(log n) 级别。

    示例 1:

    输入: nums = [4,5,6,7,0,1,2], target = 0
    输出: 4
    示例 2:

    输入: nums = [4,5,6,7,0,1,2], target = 3
    输出: -1

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/search-in-rotated-sorted-array
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 1.分两步
 *  1.1找到旋转点
 *  1.2分类查找target
 *
 * 2.异或大法
 * https://leetcode-cn.com/problems/search-in-rotated-sorted-array/solution/ji-jian-solution-by-lukelee/
 *
 *
 * 3.二分法
 *  以旋转点为界限，数组被分成左半段和右半段升序的序列。
 *  比较nums[mid]和nums[l]的大小。判断mid落在左半段还是右半段。
 *  nums[mid]>=nums[l]：mid在左半段
 *      若有 nums[l]<= target < nums[mid]
 *          此时，target在l和mid之间，有r = mid - 1；
 *      否则，target<nums[l]或者target>nums[mid]
 *          target都在mid的右边，有l = mid + 1;
 *  nums[mid]<nums[l]：mid在右半段
 *      若有 nums[mid]< target <= nums[r]
 *          此时，target在mid和r之间，有l = mid + 1；
 *      否则，target>nums[r]或者target<nums[mid]
 *          target都在mid的左边，有r = mid - 1;
 *
 */


class Solution {
public:
    //旋转点
    int pivot(vector<int>& nums,int left,int right){
        //nums[left] < nums[right] 数组升序，没旋转
        if(nums[left] < nums[right]) return 0;
        while(left<right){
            int mid = left + ((right - left) >> 1);
            if(nums[mid] > nums[right]){
                left = mid+1;
            }else{
                right = mid;
            }
        }
        return left;
    }
    //二分搜索
    int func(vector<int>& nums,int left,int right,int target){
        while(left<=right){
            int mid = left + ((right - left) >> 1);
            if(nums[mid]==target) return mid;
            else if(nums[mid] > target){
                right = mid-1;
            }else{
                left = mid+1;
            }
        }
        return -1;
    }
    int search(vector<int>& nums, int target) {
        if(nums.size()==0) return -1;
        int p = pivot(nums,0,nums.size()-1);
        if(nums[0]==target) return 0;
        //分三类
        if(p==0) return func(nums,0,nums.size()-1,target);
        if(nums[0] > target)return func(nums,p,nums.size()-1,target);
        return func(nums,0,p-1,target);
    }
};


class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            //分类。
            // 三个条件中满足两个 向右
            // 三个条件中满足一个 向左
            if ((nums[0] > target) ^ (nums[0] > nums[mid]) ^ (target > nums[mid]))
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo == hi && nums[lo] == target ? lo : -1;
    }
};

//https://leetcode-cn.com/problems/search-in-rotated-sorted-array/solution/ji-bai-liao-9983de-javayong-hu-by-reedfan/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size()==0)return -1;
        int n = nums.size();
        int l = 0, r = n-1;
        while(l<=r){
            int mid = l + ((r - l) >> 1);
            if(nums[mid]==target) return mid;
            //判断mid在左半段还是右半段
            if(nums[mid]>=nums[l]){
                //判断target在mid的左边还是右边
                if(nums[l]<=target&&target<nums[mid]){
                    r = mid - 1;
                }else{
                    l = mid + 1;
                }
            }else{
                if(nums[mid]<target&&target<=nums[r]){
                    l = mid + 1;
                }else{
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};
