// @File   : 503_nextGreaterElements.cpp
// @Source : https://leetcode-cn.com/problems/next-greater-element-ii/
// @Title  : 503. 下一个更大元素 II
// @Auther : sun_ds
// @Date   : 2020/3/1

/**  题目描述：
    给定一个循环数组（最后一个元素的下一个元素是数组的第一个元素），输出每个元素的下一个更大元素。数字 x 的下一个更大的元素是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1。

    示例 1:

    输入: [1,2,1]
    输出: [2,-1,2]
    解释: 第一个 1 的下一个更大的数是 2；
    数字 2 找不到下一个更大的数；
    第二个 1 的下一个最大的数需要循环搜索，结果也是 2。
    注意: 输入数组的长度不会超过 10000。



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/next-greater-element-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 循环数组中各元素的下一个更大的元素
 *
 * 1.单调栈
 * 对于正常数组。
 * 遍历数组，构造单调递减栈，当不满足递减规则时，栈内的元素需要出栈，代表该出栈元素第一个右边的更大的值为当前的值。
 * 单调栈中存储的是元素在数组中的索引。
 * 以出栈元素在数组中的索引作为索引，存储当前需要入栈的值，即得到各元素的下一个更大的元素。
 *
 * 对于循环数组。
 * 将数组扩展成2倍长度即可。
 *
 *
 *
 *
 *
 */

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        stack<int> s;
        vector<int> res(n,-1);
        //循环数组。遍历两遍
        for(int i=0;i<2*n;i++){
            while(!s.empty()&&nums[s.top()]<nums[i%n]){
                res[s.top()] = nums[i%n];
                s.pop();
            }
            s.push(i%n);
        }
        return res;
    }
};