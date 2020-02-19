// @File   : 3_findRepeatNumber.cpp
// @Source : https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/
// @Title  : 面试题03. 数组中重复的数字
// @Auther : sun_ds
// @Date   : 2020/2/16

/**  题目描述：
    找出数组中重复的数字。


    在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

    示例 1：

    输入：
    [2, 3, 1, 0, 2, 5, 3]
    输出：2 或 3
     

    限制：

    2 <= n <= 100000



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/



/**
 *
 * 找出数组中重复的元素
 *
 * 注意条件，长度为n的数组的数字取值在0~n-1之间。可以证明，一个萝卜一个坑，
 * 即可以将nums[i]的这个值都放到自己对应的坐标位置，形成所有的nums[i] == i的最终局面。
 *
 * 1.hash
 *  使用hash表存储，找到重复的数字。
 *
 * 2.不使用额外空间
 *  将nums数组当成一个特殊的hash表，即该表中都有nums[i] == i
 *  因此，遍历，判断是否满足nums[i] == i若不满足，
 *  则看自己应该在的位置的值nums[nums[i]]是否与自己nums[i]相等，如果相等，说明坑被别人抢先一步，说明该值nums[i]出现重复。
 *  否则，将nums[i]和nums[nums[i]]的值相互交换，将nums[i]这个值放对位置。
 *
 *
 *
 *
 *
 */



//hash表存储
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        unordered_map<int,int> m;
        m.clear();
        for(auto i:nums){
            m[i]++;
            if(m[i] > 1) return i;
        }
        return -1;
    }
};

//一个萝卜一个坑
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        for(int i=0;i<nums.size();++i){
            while(nums[i]!=i){   //一个萝卜一个坑
                if(nums[i] == nums[nums[i]]){  //坑被占了
                    return nums[i];
                }
                int temp = nums[i];  //交换到自己的坑去
                nums[i] = nums[temp];
                nums[temp] = temp;
            }
        }
        return -1;
    }
};



