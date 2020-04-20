// @File   : 155_MinStack.cpp
// @Source : https://leetcode-cn.com/problems/min-stack/
// @Title  : 155. 最小栈
// @Auther : sun_ds
// @Date   : 2020/3/19

/**  题目描述：
    设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。

    push(x) -- 将元素 x 推入栈中。
    pop() -- 删除栈顶的元素。
    top() -- 获取栈顶元素。
    getMin() -- 检索栈中的最小元素。
    示例:

    MinStack minStack = new MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    minStack.getMin();   --> 返回 -3.
    minStack.pop();
    minStack.top();      --> 返回 0.
    minStack.getMin();   --> 返回 -2.
*/


/**
 *
 * 使用辅助栈保存最小值
 * 辅助栈，单调递减
 */

class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> s1,s2;
    MinStack() {

    }

    void push(int x) {
        s1.push(x);
        if(s2.empty()||s2.top()>=x) s2.push(x);
    }

    void pop() {
        int temp = s1.top();
        if(s2.top()==temp) s2.pop();
        s1.pop();
    }

    int top() {
        return s1.top();
    }

    int getMin() {
        return s2.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

