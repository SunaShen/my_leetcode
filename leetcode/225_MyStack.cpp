// @File   : 225_MyStack.cpp
// @Source : https://leetcode-cn.com/problems/implement-stack-using-queues/
// @Title  : 225. 用队列实现栈
// @Auther : sun_ds
// @Date   : 2020/3/1

/**  题目描述：
    使用队列实现栈的下列操作：

    push(x) -- 元素 x 入栈
    pop() -- 移除栈顶元素
    top() -- 获取栈顶元素
    empty() -- 返回栈是否为空
    注意:

    你只能使用队列的基本操作-- 也就是 push to back, peek/pop from front, size, 和 is empty 这些操作是合法的。
    你所使用的语言也许不支持队列。 你可以使用 list 或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。
    你可以假设所有操作都是有效的（例如, 对一个空的栈不会调用 pop 或者 top 操作）。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/implement-stack-using-queues
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 * 使用队列来实现栈
 *
 * 队列：先进先出 栈：先进后出
 *
 * 1.双队列
 *  使用双队列，一个作为辅助队列。
 *  将数push进队列q1，并记录top = 当前push的vaule
 *  需要top。输出top
 *  需要pop。即需将q1队尾元素输出。将q1前n-1个出队到q2，则只剩需要的队尾，将他pop。并将q2与q1交换。继续。
 *
 *  下面减少交换使用flag标记，交替使用q1和q2.
 *  下面top的方法有点笨拙了。使用类似pop的方法才能获得top。
 *
 * 2.单队列
 *  使用单队列
 *  在每次push之后，都将前n-1个队头依次搬到队尾。
 *  int temp = q.top();
 *  q.pop();
 *  q.push(temp);
 *  这样该队列一直维持着类似栈的顺序。
 *
 *
 *
 */



//双队列
class MyStack {
public:
    queue<int> q1,q2;
    int flag = 0;
    /** Initialize your data structure here. */
    MyStack() {

    }

    /** Push element x onto stack. */
    void push(int x) {
        if(flag == 0)
            q1.push(x);
        else
            q2.push(x);
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int res = 0;
        if(flag == 0){
            int n = q1.size();
            for(int i=0;i<n-1;i++){
                q2.push(q1.front());
                q1.pop();
            }
            res = q1.front();
            q1.pop();
            flag = 1;
        }else{
            int n = q2.size();
            for(int i=0;i<n-1;i++){
                q1.push(q2.front());
                q2.pop();
            }
            res = q2.front();
            q2.pop();
            flag = 0;
        }
        return res;
    }

    /** Get the top element. */
    int top() {
        int res = 0;
        if(flag == 0){
            int n = q1.size();
            for(int i=0;i<n-1;i++){
                q2.push(q1.front());
                q1.pop();
            }
            res = q1.front();
        }else{
            int n = q2.size();
            for(int i=0;i<n-1;i++){
                q1.push(q2.front());
                q2.pop();
            }
            res = q2.front();
        }
        return res;
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return q1.size()+q2.size() == 0;
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 *  paraintm_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

// 单队列
class MyStack {
private:
    queue<int> q;
public:
    /** Initialize your data structure here. */
    MyStack() {

    }

    /** Push element x onto stack. */
    void push(int x) {
        // 反转队列，将新元素插到队头
        int n = q.size();
        q.push(x);
        while(n>0){
            int temp = q.front();
            q.pop();
            q.push(temp);
            n--;
        }
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int res = q.front();
        q.pop();
        return res;
    }

    /** Get the top element. */
    int top() {
        return q.front();
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 *  paraintm_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */