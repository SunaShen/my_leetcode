// @File   : 84_largestRectangleArea.cpp
// @Source : https://leetcode-cn.com/problems/largest-rectangle-in-histogram/
// @Title  : 84. 柱状图中最大的矩形
// @Auther : sun_ds
// @Date   : 2020/4/4

/**  题目描述：
    给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

    求在该柱状图中，能够勾勒出来的矩形的最大面积。

     



    以上是柱状图的示例，其中每个柱子的宽度为 1，给定的高度为 [2,1,5,6,2,3]。

     



    图中阴影部分为所能勾勒出的最大矩形面积，其面积为 10 个单位。

     

    示例:

    输入: [2,1,5,6,2,3]
    输出: 10

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/largest-rectangle-in-histogram
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 题目理解。柱状图中每个位置有高度。
 * 找到最高矩形面积，该面积是由当前位置的高度为矩形高的。     *由当前高度为矩形高度*
 * 要求当前围成的面积，需要找到该位置左右两边比当前高度小的位置。
 * 那么矩形的宽度为r-l-1。则当前位置矩形面积为 heights[i] * (r - l - 1).
 *
 *
 * 1.单调栈
 * 维护一个单调递增栈。
 * 当插入元素小于栈顶时，插入元素位置i即为栈顶右边的小于自己的位置。
 * 而由于单调递增栈性质，栈顶左边为左边小于自己的位置。
 * 所以。计算栈顶位置组成的最大矩形为
 * 栈顶高度 int h = heights[s.top()]. s.pop(). 为了取得栈顶左端位置，需要当前栈顶pop  重要！！！
 * 此时s.pop()为左边小于自己的位置。
 * 则最大矩形面积为 h*(i-s.pop()-1).
 *
 * 为了使得所有位置矩形面积都被计算到，需要添加哨兵。
 *
 * 在heights末尾添加小于最小值的元素即可，这里添加0.
 * 还有一个问题，当栈中只有最后一个元素时，他虽然后面有哨兵逼自己出来，但是前面没有存储比自己小的位置了，导致不能计算矩形宽。
 * 所以，在heights最前端也添加小于最小值的元素。使得真正有效的最后一个值也能正常计算。
 *
 * 前后哨兵，在heights前后各添加一个小于最小值的元素。使得边界处理完全。
 *
 * 最后执行完，栈里面剩了两个哨兵。。。
 *
 * 42. 接雨水中，左右都不需要哨兵。
 * 121. 买卖股票的最佳时机，右端需要哨兵 但需要栈底。所以用vector实现
 *
 *
 *
 */

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> s;
        //前后哨兵
        heights.insert(heights.begin(),0);
        heights.push_back(0);
        int res = 0;
        for(int i=0;i<heights.size();i++){
            while(!s.empty()&&heights[s.top()]>heights[i]){
                int index = s.top(); s.pop();
                while(!s.empty()&&heights[s.top()]==heights[index]){
                    s.pop();
                }
                res = max(res,heights[index] * (i - s.top() - 1));
            }
            s.push(i);
        }
        return res;
    }
};

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> s;
        //前后哨兵
        heights.insert(heights.begin(),0);
        heights.push_back(0);
        int res = 0;
        for(int i=0;i<heights.size();i++){
            while(!s.empty()&&heights[s.top()]>heights[i]){
                int index = s.top(); s.pop();
                //很重要
                //先取出当前index并pop 矩形高度为heights[index]
                //矩形宽度比heights[index]小的两边。
                //右边为i 左边为 当前的s.top()
                res = max(res,heights[index] * (i - s.top() - 1));
            }
            s.push(i);
        }
        return res;
    }
};

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> s;
        //前后哨兵
        //位置必须为-1，为了能够计算矩形宽
        s.push(-1);
        heights.push_back(0);
        int res = 0;
        for(int i=0;i<heights.size();i++){
            while(s.size()>1&&heights[s.top()]>heights[i]){
                int index = s.top(); s.pop();
                //很重要
                //先取出当前index并pop 矩形高度为heights[index]
                //矩形宽度比heights[index]小的两边。
                //右边为i 左边为 当前的s.top()
                res = max(res,heights[index] * (i - s.top() - 1));
            }
            s.push(i);
        }
        return res;
    }
};


