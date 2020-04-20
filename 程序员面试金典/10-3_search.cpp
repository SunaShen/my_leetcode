// @File   : 10-3_search.cpp
// @Source : https://leetcode-cn.com/problems/search-rotate-array-lcci/
// @Title  : 面试题 10.03. 搜索旋转数组
// @Auther : sun_ds
// @Date   : 2020/3/31

/**  题目描述：
    搜索旋转数组。给定一个排序后的数组，包含n个整数，但这个数组已被旋转过很多次了，次数不详。请编写代码找出数组中的某个元素，假设数组元素原先是按升序排列的。若有多个相同元素，返回索引值最小的一个。

    示例1:

     输入: arr = [15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14], target = 5
     输出: 8（元素5在该数组中的索引）
    示例2:

     输入：arr = [15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14], target = 11
     输出：-1 （没有找到）
    提示:

    arr 长度范围在[1, 1000000]之间

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/search-rotate-array-lcci
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.分两步(注意重复)
 *  1.1找到旋转点
 *  1.2分类查找target
 *
 */

class Solution {
public:
    //旋转点(注意重复)
    int pivot(vector<int>& nums,int left,int right){
        //nums[left] < nums[right] 数组升序，没旋转
        if(nums[left] < nums[right]) return 0;
        while(left<right){
            int mid = left + ((right - left) >> 1);
            if(nums[mid] == nums[right]){
                right = right - 1;
            }else if(nums[mid] > nums[right]){
                left = mid+1;
            }else{
                right = mid;
            }
        }
        return left;
    }
    //二分搜索(最左端匹配)
    int func(vector<int>& nums,int left,int right,int target){
        while(left<=right){
            int mid = left + ((right - left) >> 1);
            if(nums[mid] >= target){
                right = mid-1;
            }else{
                left = mid+1;
            }
        }
        if(left<nums.size()&&nums[left]==target) return left;
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



