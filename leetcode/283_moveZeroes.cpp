// @File   : 283_moveZeroes.cpp
// @Source : https://leetcode-cn.com/problems/move-zeroes/
// @Title  : 283. 移动零
// @Auther : sun_ds
// @Date   : 2020/4/22

/**  题目描述：
    给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

    示例:

    输入: [0,1,0,3,12]
    输出: [1,3,12,0,0]
    说明:

    必须在原数组上操作，不能拷贝额外的数组。
    尽量减少操作次数。


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/move-zeroes
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 双指针？
 * i遍历数组，j表示没有除去0，数字排列的位置。
 * 遇到不是0的数就往前放
 * 最后的位置补0
 *
 */

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int j=0;
        for(int i=0;i<n;i++){
            if(nums[i]==0) continue;
            nums[j++] = nums[i];
        }
        for(;j<n;j++){
            nums[j] = 0;
        }
    }
};

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        for(int j=0,i=0;i<n;i++){
            if(nums[i]==0) continue;
            swap(nums[j],nums[i]);
            j++;
        }
    }
};
