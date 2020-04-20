// @File   : 53-1_search.cpp
// @Source : https://leetcode-cn.com/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof/
// @Title  : 面试题53 - I. 在排序数组中查找数字 I
// @Auther : sun_ds
// @Date   : 2020/3/30

/**  题目描述：
    统计一个数字在排序数组中出现的次数。

     

    示例 1:

    输入: nums = [5,7,7,8,8,10], target = 8
    输出: 2
    示例 2:

    输入: nums = [5,7,7,8,8,10], target = 6
    输出: 0
     

    限制：

    0 <= 数组长度 <= 50000

     

    注意：本题与主站 34 题相同（仅返回值不同）：https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 1.二分找到target最前面的位置后遍历统计到不是target的位置
 *
 * 2.两次二分分别找到target的左右边界
 *
 * 3.使用lower_bound 和 upper_bound
 *
 *
 */


class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0,r = nums.size()-1;
        while(l<=r){
            int mid = l + ((r - l)>>1);
            if(nums[mid]<target){
                l = mid + 1;
            }else{
                r = mid - 1;
            }
        }
        int count = 0;
        for(int i=l;i<nums.size();i++){
            if(nums[i]==target) count++;
            else break;
        }
        return count;
    }
};


class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0,r = nums.size()-1;
        while(l<=r){
            int mid = l + ((r - l)>>1);
            if(nums[mid]<target){
                l = mid + 1;
            }else{
                r = mid - 1;
            }
        }
        int left = r;
        l = 0;
        r = nums.size()-1;
        while(l<=r){
            int mid = l + ((r - l)>>1);
            if(nums[mid]<=target){
                l = mid + 1;
            }else{
                r = mid - 1;
            }
        }
        int right = l;
        return right - left - 1;
    }
};

class Solution {
public:
    int search(vector<int>& nums, int target) {
        return (upper_bound(nums.begin(),nums.end(),target) - lower_bound(nums.begin(),nums.end(),target));
    }
};

