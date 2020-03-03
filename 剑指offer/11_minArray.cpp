// @File   : 11_minArray.cpp
// @Source : https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/
// @Title  : 面试题11. 旋转数组的最小数字
// @Auther : sun_ds
// @Date   : 2020/3/3

/**  题目描述：
    把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。  

    示例 1：

    输入：[3,4,5,1,2]
    输出：1
    示例 2：

    输入：[2,2,2,0,1]
    输出：0
    注意：本题与主站 154 题相同：https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 找到旋转数组的最小数字
 * 注意：包含重复数字
 *
 *
 * 1.暴力法
 *  遍历数组找到最小值。
 *
 * 2.二分法
 * while(i<j)
 * 执行完循环的条件是i==j
 *
 * 比较nums[mid] 和 nums[r]的大小。
 *   1. nums[mid] > nums[r] 最小值在mid的右半部分，且不是mid  所以l = mid+1
 *   2. nums[mid] < nums[r] 最小值在mid的左半部分，且可能是mid 所以r = mid
 *   3. nums[mid] == nums[r] 无法判断最小值在左半部分还是右半部分 执行r = r-1
 *     验证r = r-1的正确性
 *     3.1. mid是最小值或在最小值右侧，则[mid，r]之间的值都相等，由于i<j 所以mid!=j，执行r=r-1减少一个重复的数，不影响
 *     3.2. mid在最小值左侧
 *       3.2.2. 最小值小于nums[r] 执行r=r-1，最小值还在区间内。
 *       3.2.1. 最小值等于nums[r]
 *         3.2.1.1. 当前r不是旋转点，则旋转点在r左侧，执行r = r-1 不影响
 *         3.2.1.2. 当前r就是旋转点，继续执行r = r-1 则区间变成递增区间。
 *                   继续执行，会找到最左端nums[l].且nums[mid] == nums[r] 所以nums[l] = nums[r].所以旋转点的值还是对的。
 *
 * 特殊情况[1,3,3,3,3,3,3,3,3] 每次都执行r = r-1 复杂度退化到O(N)
 *
 * https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof/solution/mian-shi-ti-11-xuan-zhuan-shu-zu-de-zui-xiao-shu-3/
 * 3.递归
 *  递归的方式执行二分？
 *  在nums[mid]==nums[end]不知道旋转点在左还是右的情况下，拆成两部分，都算一遍取最小值。
 *  且使用mid>0&&nums[mid]<nums[mid-1]条件，提前验证nums[mid]是不是旋转点
 *
 *
 */

//二分法
class Solution {
public:
    int minArray(vector<int>& numbers) {
        int l = 0, r = numbers.size() - 1;
        while(l<r){
            int mid = l + ((r - l) >> 1);
            if(numbers[mid]==numbers[r]){
                //重点
                r = r-1;
            }else if(numbers[mid]>numbers[r]){
                l = mid + 1 ;
            }else{
                r = mid;
            }
        }
        return numbers[l];
    }
};

//递归
class Solution {
public:
    int find(vector<int>& nums,int begin,int end)
    {
        while(begin<end)
        {
            if(nums[begin]<nums[end])
                return nums[begin];
            int mid = begin+(end-begin)/2;
            if(mid>0&&nums[mid]<nums[mid-1]) //nums[mid]<nums[mid-1] 则mid必是旋转点
                return nums[mid];//提前判断
            if(nums[mid]==nums[end]) //相等无法判断
                return min(find(nums,begin,mid-1),find(nums,mid+1,end)); //分两部分 nums[mid]不是旋转点，前面判断过了
            else if(nums[mid]<nums[begin])
                end = mid;
            else
                begin=mid+1;
        }
        return nums[begin];
    }
    int minArray(vector<int>& nums) {
        return find(nums,0,nums.size()-1);
    }
};

