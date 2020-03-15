// @File   : 30_MinStack.cpp
// @Source : https://leetcode-cn.com/problems/bao-han-minhan-shu-de-zhan-lcof/
// @Title  : 面试题30. 包含min函数的栈
// @Auther : sun_ds
// @Date   : 2020/3/13

/**  题目描述：
    定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，调用 min、push 及 pop 的时间复杂度都是 O(1)。

     

    示例:

    MinStack minStack = new MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    minStack.min();   --> 返回 -3.
    minStack.pop();
    minStack.top();      --> 返回 0.
    minStack.min();   --> 返回 -2.
     

    提示：

    各函数的调用总次数不超过 20000 次
     

    注意：本题与主站 155 题相同：https://leetcode-cn.com/problems/min-stack/

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/bao-han-minhan-shu-de-zhan-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 维护一个辅助栈，栈中是递减形式。
 * 知道当输入的值小于辅助栈顶才入辅助栈。否则不操作。(辅助栈为空直接入栈)
 * pop时，如果s的栈顶等于辅助栈顶，则同时出栈。
 * 辅助栈顶即为当前栈中的最小元素。
 *
 *
 *
 */



class MinStack {
    stack<int> s,m_s;
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
        s.push(x);
        if(m_s.empty()||x<=m_s.top()) m_s.push(x);
    }

    void pop() {
        int temp = s.top();
        if(temp==m_s.top()) m_s.pop();
        s.pop();
    }

    int top() {
        return s.top();
    }

    int min() {
        return m_s.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */

