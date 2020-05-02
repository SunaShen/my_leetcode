// @File   : 17.21_trap.cpp
// @Source : https://leetcode-cn.com/problems/volume-of-histogram-lcci/
// @Title  : 面试题 17.21. 直方图的水量
// @Auther : sun_ds
// @Date   : 2020/4/4

/**  题目描述：
    给定一个直方图(也称柱状图)，假设有人从上面源源不断地倒水，最后直方图能存多少水量?直方图的宽度为 1。



    上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的直方图，在这种情况下，可以接 6 个单位的水（蓝色部分表示水）。 感谢 Marcos 贡献此图。

    示例:

    输入: [0,1,0,2,1,0,1,3,2,1,2,1]
    输出: 6

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/volume-of-histogram-lcci
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.单调栈
 * 维护单调递减栈。当有元素大于栈顶，则找到了栈顶右边的大于自己的位置。而栈顶的左边为大于自己的左边的位置。
 * 由此可以计算当前凹槽的面积。
 * int index = s.top(),s.pop().当前出栈是为了去左边的位置。
 * 当前凹槽水量，heights[index]*(i - s.pop() - 1)
 * 当前index已经出栈了。
 * 下次在计算，当前index位置默认已经被填平了。不需考虑了。
 * 2.dp
 * m1保存当前位置左端最大值
 * m2保存当前位置右端最大值
 *
 * 遍历，当前位置上方的水量为 min(m1[i],m2[i]) - heights[i].
 * 当然，前提是min(m1[i],m2[i]) > heights[i]
 * 而i=0和i=n-1是都不会有水的。
 * 如果需要计算i=0和i=n-1的水量，需要加哨兵。
 *
 *
 */

//单调栈
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> s;
        int res=0;
        for(int i=0;i<height.size();i++){
            while(!s.empty()&&height[s.top()]<height[i]){
                int index = s.top(); s.pop();
                if(!s.empty()){
                    res += (min(height[s.top()],height[i]) - height[index])*(i - s.top() - 1);
                }
            }
            s.push(i);
        }
        return res;
    }
};

//dp
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int res = 0;
        vector<int> m1(n,0);
        vector<int> m2(n,0);
        //当前位置左端最大值
        for(int i=1;i<n;i++){
            m1[i] = max(m1[i-1],height[i-1]);
        }
        //当前位置右端最大值
        for(int i=n-2;i>=0;i--){
            m2[i] = max(m2[i+1],height[i+1]);
        }
        for(int i=1;i<n-1;i++){
            res += min(m1[i],m2[i]) > height[i] ? min(m1[i],m2[i]) - height[i] : 0;
        }
        return res;
    }
};