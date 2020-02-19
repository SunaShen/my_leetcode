// @File   : 9_CQueue.cpp
// @Source : https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/
// @Title  : 面试题09. 用两个栈实现队列
// @Auther : sun_ds
// @Date   : 2020/2/19

/**  题目描述：
    用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )

     

    示例 1：

    输入：
    ["CQueue","appendTail","deleteHead","deleteHead"]
    [[],[3],[],[]]
    输出：[null,null,3,-1]
    示例 2：

    输入：
    ["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]
    [[],[],[5],[2],[],[]]
    输出：[null,-1,null,null,5,2]
    提示：

    1 <= values <= 10000
    最多会对 appendTail、deleteHead 进行 10000 次调用

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * s1负责入，s2负责出。
 * s2的值由s1出栈后又入栈组成。则s2的栈顶即为最先进入的数，满足先入先出。
 * s2中没有元素可以输出时，从s1出栈后入栈来补充。
 *
 */


class CQueue {
public:
    stack<int> s1,s2;
    CQueue() {

    }

    void appendTail(int value) {
        s1.push(value);
    }

    int deleteHead() {
        int ans = -1;
        if(!s2.empty()){
            ans = s2.top();
            s2.pop();
        }else{
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
            if(!s2.empty()){
                ans = s2.top();
                s2.pop();
            }
        }
        return ans;
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */