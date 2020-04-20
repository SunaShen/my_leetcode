// @File   : 41_MedianFinder.cpp
// @Source : https://leetcode-cn.com/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof/
// @Title  : 面试题41. 数据流中的中位数
// @Auther : sun_ds
// @Date   : 2020/3/28

/**  题目描述：
    如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

    例如，

    [2,3,4] 的中位数是 3

    [2,3] 的中位数是 (2 + 3) / 2 = 2.5

    设计一个支持以下两种操作的数据结构：

    void addNum(int num) - 从数据流中添加一个整数到数据结构中。
    double findMedian() - 返回目前所有元素的中位数。
    示例 1：

    输入：
    ["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
    [[],[1],[2],[],[3],[]]
    输出：[null,null,null,1.50000,null,2.00000]
    示例 2：

    输入：
    ["MedianFinder","addNum","findMedian","addNum","findMedian"]
    [[],[2],[],[3],[]]
    输出：[null,null,2.00000,null,2.50000]
     

    限制：

    最多会对 addNum、findMedia进行 50000 次调用。
    注意：本题与主站 295 题相同：https://leetcode-cn.com/problems/find-median-from-data-stream/



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof
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

