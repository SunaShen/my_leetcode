// @File   : 238_productExceptSelf.cpp
// @Source : https://leetcode-cn.com/problems/product-of-array-except-self/
// @Title  : 238. 除自身以外数组的乘积
// @Auther : sun_ds
// @Date   : 2020/6/4

/**  题目描述：
    给你一个长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。

     

    示例:

    输入: [1,2,3,4]
    输出: [24,12,8,6]
     

    提示：题目数据保证数组之中任意元素的全部前缀元素和后缀（甚至是整个数组）的乘积都在 32 位整数范围内。

    说明: 请不要使用除法，且在 O(n) 时间复杂度内完成此题。

    进阶：
    你可以在常数空间复杂度内完成这个题目吗？（ 出于对空间复杂度分析的目的，输出数组不被视为额外空间。）

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/product-of-array-except-self
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.前缀乘积 后缀乘积
 * 使用 front 和 back 分别记录前后缀乘积
 * 则当前位置的结果为 front*back
 *
 * 遍历顺序相同，可以使用一个变量来表示 front ，这样节省空间。
 *
 * 使用 res 来代替 back 进一步节省空间。
 *
 *
 */



class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();

        vector<int> res(n);
        vector<int> front(n);
        vector<int> back(n);

        front[0] = 1;
        for(int i=1;i<n;i++){
            front[i] = front[i-1]*nums[i-1];
        }

        back[n-1] = 1;
        for(int i=n-2;i>=0;i--){
            back[i] = back[i+1]*nums[i+1];
        }

        for(int i=0;i<n;i++){
            res[i] = front[i]*back[i];
        }

        return res;
    }
};


class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();

        vector<int> res(n);
        vector<int> back(n);
        back[n-1] = 1;
        for(int i=n-2;i>=0;i--){
            back[i] = back[i+1]*nums[i+1];
        }

        int front = 1;
        for(int i=0;i<n;i++){
            res[i] = front*back[i];
            front *= nums[i];
        }

        return res;
    }
};

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();

        vector<int> res(n);

        res[n-1] = 1;
        for(int i=n-2;i>=0;i--){
            res[i] = res[i+1]*nums[i+1];
        }

        int front = 1;
        for(int i=0;i<n;i++){
            res[i] = front*res[i];
            front *= nums[i];
        }

        return res;
    }
};

