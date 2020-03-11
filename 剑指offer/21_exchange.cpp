// @File   : 21_exchange.cpp
// @Source : https://leetcode-cn.com/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof/
// @Title  : 面试题21. 调整数组顺序使奇数位于偶数前面
// @Auther : sun_ds
// @Date   : 2020/3/8

/**  题目描述：
    输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。

     

    示例：

    输入：nums = [1,2,3,4]
    输出：[1,3,2,4]
    注：[3,1,2,4] 也是正确的答案之一。
     

    提示：

    1 <= nums.length <= 50000
    1 <= nums[i] <= 10000


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.双指针
 *  l和r 保证l左边都是奇数 r右边都是偶数
 *  1.1 单向移动
 *  当 nums[l] 为偶数，nums[l]与nums[r]交换 并且r--; 而l不变，因为从nums[r]换过来的值还没判断。
 *  当 nums[l] 为奇数，满足条件 l++
 *  使用循环while(l<j)，循环结束时，l==r  l左边全是奇数。r右边全是偶数。 l==r这个位置不用判断了，他是奇数偶数都可以。
 *  1.2 双向移动
 *  当 nums[l] 为奇数，满足条件 l++;当 nums[r] 为偶数 r--;
 *  交换nums[l]和nums[r]
 *  两头向中间移动，减少交换次数
 * 2.快慢指针
 *  一个指针表示他左边全是奇数，另一个指针从0~n-1遍历。遇到奇数，将该数与第一个指针的数交换。
 *
 */

class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int l = 0, r = nums.size()-1;
        while(l<r){
            //偶数交换到后面去
            if(nums[l]%2==0){
                int temp = nums[r];
                nums[r] = nums[l];
                nums[l] = temp;
                r--;
            }else{
                l++;
            }
        }
        return nums;
    }
};


class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int l = 0, r = nums.size()-1;
        while(l<r){
            //两头开工。减少交换次数。
            while(l<r&&nums[l]%2==1) l++;
            while(l<r&&nums[r]%2==0) r--;
            int temp = nums[r];
            nums[r] = nums[l];
            nums[l] = temp;
        }
        return nums;
    }
};

class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int low = 0, fast = 0;
        while (fast < nums.size()) {
            if (nums[fast] & 1) {
                swap(nums[low], nums[fast]);
                low ++;
            }
            fast ++;
        }
        return nums;
    }
};
