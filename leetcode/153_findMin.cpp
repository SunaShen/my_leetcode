// @File   : 153_findMin.cpp
// @Source : https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/
// @Title  : 寻找旋转排序数组中的最小值
// @Auther : sun_ds
// @Date   : 2020/1/8

/**  题目描述：
    假设按照升序排序的数组在预先未知的某个点上进行了旋转。

    ( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

    请找出其中最小的元素。

    你可以假设数组中不存在重复元素。

    示例 1:

    输入: [3,4,5,1,2]
    输出: 1
    示例 2:

    输入: [4,5,6,7,0,1,2]
    输出: 0

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 获取升序排列数组的旋转数组中的最小值
 * 最小值位于不满足升序的间断点处
 *
 * 1.暴力法
 *  遍历数组，获得最小值
 *  时间复杂度O(n)
 *
 * 2.二分法
 *  使用nums[mid]与nums[r]进行比较（也可与nums[l],由旋转特性知nums[l]只是略大于nums[r]）
 *   若nums[mid] > nums[r] 则最小值在mid右侧 l = mid + 1
 *   若nums[mid] <= nums[r] 则最小值在mid左侧 r = mid
 *  循环判断l<r 跳出循环时即l=r。即此时nums[l]=nums[r]为最小值
 *
 *  时间复杂度O(logn)
 *
 * 3.二分法+判断 提前结束
 *  在二分法的过程中，增加三个判断条件，提前结束，提前return
 *   nums[mid] > nums[r]时,若nums[mid]>nums[mid+1] 不满足升序的位置 则nums[mid+1]为最小值，return nums[mid+1]
 *   nums[mid] <= nums[r]时,若nums[mid] > nums[l] 则有nums[l]<nums[mid]<=nums[r]，则该数组就是升序的，因此nums[l]是最小值。return nums[l]
 *   nums[mid] <= nums[r]时,若mid = 0 || nums[mid - 1] > nums[mid]时, 则nums[mid]即为最小值。return nums[mid]。/
 *     其中，mid=0=l，则nums[l] = nums[mid]就是最小值，mid != 0时，nums[mid-1] > nums[mid]，则此处不满足升序，则nums[mid]为最小值。
 *  通过这些判断条件，提前结束程序，加快速度。
 *
 *
 */

//二分法
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while(l<r){
            int mid = l + ((r - l)>>1);
            if(nums[mid] > nums[r]){
                l = mid+1;
            }else{
                r = mid;
            }
        }
        return nums[l];
    }
};
//二分法，剪枝
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while(l<r){
            int mid = l + ((r - l)>>1);
            if(nums[mid] > nums[r]){
                if(nums[mid] > nums[mid+1]) return nums[mid+1];
                l = mid+1;
            }else{
                if(nums[mid] > nums[l]) return nums[l];
                if(mid == 0 || nums[mid] < nums[mid - 1]) return nums[mid];
                r = mid;
            }
        }
        return nums[l];
    }
};