// @File   : 59-2_MaxQueue.cpp
// @Source : https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof/
// @Title  : 面试题59 - II. 队列的最大值
// @Auther : sun_ds
// @Date   : 2020/3/7

/**  题目描述：
    请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数max_value、push_back 和 pop_front 的时间复杂度都是O(1)。

    若队列为空，pop_front 和 max_value 需要返回 -1

    示例 1：

    输入:
    ["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
    [[],[1],[2],[],[],[]]
    输出: [null,null,null,2,1,2]
    示例 2：

    输入:
    ["MaxQueue","pop_front","max_value"]
    [[],[],[]]
    输出: [null,-1,-1]
     

    限制：

    1 <= push_back,pop_front,max_value的总操作数 <= 10000
    1 <= value <= 10^5


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 使用O(1)复杂度获取队列中最大值。同时插入和删除也要求O(1).
 *
 * 思路：空间换时间
 *
 * 1.辅助队列
 *  使用普通队列存储元素。
 *  使用一个双端递减队列存储最大值。该双端队列队头就是当前队列中的最大值。
 *
 *  查询最大值，直接返回双端队列的队头。(如果双端队列不空的话)。
 *
 *  push时，判断插入值和双端队列队尾值的大小，若插入值大于队尾，则队尾出队，直到队尾大于等于插入值，插入值入队。
 *  以此来维持该双端队列的递减性(队首最大值)。
 *
 *  pop时，判断当前pop的值是不是双端队列的队首(最大值)。如果是的话，则也pop_front出队，最大值交给他的下一个位置。
 *
 *
 * push时判断插入值和队尾的大小使用while循环，但是每个元素只会出队一次，即while最多执行次数是队列总长度N。
 * 因此该操作均摊到N此push里面，也是具有复杂度O(1)
 *
 * 最大值时间复杂度 O(1)
 * 插入时间复杂度 O(1)
 * 删除时间复杂度 O(1)
 *
 * 空间复杂度 O(N)
 *
 *
 *
 *
 */


class MaxQueue {
    queue<int> q;
    deque<int> dq;
public:
    MaxQueue() {

    }

    int max_value() {
        if(!dq.empty()) return dq.front();
        else return -1;
    }

    void push_back(int value) {
        while( !dq.empty() && dq.back() < value){
            dq.pop_back();
        }
        q.push(value);
        dq.push_back(value);
    }

    int pop_front() {
        if(q.empty()) return -1;
        int res = q.front();
        if(res == dq.front()){
            dq.pop_front();
        }
        q.pop();
        return res;
    }
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */

