// @File   : 295_MedianFinder.cpp
// @Source : https://leetcode-cn.com/problems/find-median-from-data-stream/
// @Title  : 295. 数据流的中位数
// @Auther : sun_ds
// @Date   : 2020/3/28

/**  题目描述：
    中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。

    例如，

    [2,3,4] 的中位数是 3

    [2,3] 的中位数是 (2 + 3) / 2 = 2.5

    设计一个支持以下两种操作的数据结构：

    void addNum(int num) - 从数据流中添加一个整数到数据结构中。
    double findMedian() - 返回目前所有元素的中位数。
    示例：

    addNum(1)
    addNum(2)
    findMedian() -> 1.5
    addNum(3)
    findMedian() -> 2
    进阶:

    如果数据流中所有整数都在 0 到 100 范围内，你将如何优化你的算法？
    如果数据流中 99% 的整数都在 0 到 100 范围内，你将如何优化你的算法？

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/find-median-from-data-stream
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1.使用大顶堆和小顶堆
 *  大顶堆size等于小顶堆size或者比小顶堆size大一
 *  偶数个数时，中位数为大顶堆堆顶和小顶堆堆顶的平均数
 *  奇数个数时，中位数为大顶堆堆顶
 *
 *
 */




class MedianFinder {
private:
    priority_queue<int,vector<int>,less<int>> max_heap;
    priority_queue<int,vector<int>,greater<int>> min_heap;
public:
    /** initialize your data structure here. */
    MedianFinder() {

    }

    void addNum(int num) {
        int len = max_heap.size() + min_heap.size();
        //判断插入的位置
        if(len&1){ //奇数
            if(!max_heap.empty()&&num<max_heap.top()){
                int temp = max_heap.top();
                max_heap.pop();
                max_heap.push(num);
                num = temp;
            }
            min_heap.push(num);
        }else{   //偶数
            if(!min_heap.empty()&&num>min_heap.top()){
                int temp = min_heap.top();
                min_heap.pop();
                min_heap.push(num);
                num = temp;
            }
            max_heap.push(num);
        }
    }

    double findMedian() {
        int len = max_heap.size() + min_heap.size();
        double res;
        if(len&1){ //奇数
            res = max_heap.top();
        }else{  //偶数
            res = (max_heap.top() + min_heap.top())/2.0;
        }
        return res;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */


