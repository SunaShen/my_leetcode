// @File   : 40_getLeastNumbers.cpp
// @Source : https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof/
// @Title  : 面试题40. 最小的k个数
// @Auther : sun_ds
// @Date   : 2020/3/15

/**  题目描述：
    输入整数数组 arr ，找出其中最小的 k 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。

     

    示例 1：

    输入：arr = [3,2,1], k = 2
    输出：[1,2] 或者 [2,1]
    示例 2：

    输入：arr = [0,1,2,1], k = 1
    输出：[0]
     

    限制：

    0 <= k <= arr.length <= 10000
    0 <= arr[i] <= 10000


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 *
 * 1.小顶堆
 *  放入小顶堆，去除k个值即为前k小的值。
 *
 * 2.快排思想
 *  如果partition<k 则，partition前的数都是前k小。左边界从partition+1开始找剩下的
 *  如果partition>k 则，右边界变到partition-1，继续寻找。
 * 直到找到k个值。
 *
 */



//小顶堆
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> res;
        if (k == 0) return res;
        priority_queue<int, vector<int>, greater<int>> heap(arr.begin(), arr.end());
        res.resize(k);
        for (int i = 0; i < k; i++) {
            res[i] = heap.top();
            heap.pop();
        }
        return res;
    }
};


//快排思想
class Solution {
public:
    int partition(vector<int> &arr, int p, int r) {
        int i = p;
        for (int j = p; j < r; j++) {
            if (arr[j] < arr[r]) {
                swap(arr[i], arr[j]);
                i++;
            }
        }
        swap(arr[i], arr[r]);
        return i;
    }
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int> res;
        if (k == 0) return res;
        res.reserve(k);
        int low = 0, high = arr.size() - 1;
        while (res.size() != k) {
            int index = partition(arr, low, high);
            if (index - low + 1 <= k - res.size()) {
                for (int i = low; i <= index; i++) {
                    res.push_back(arr[i]);
                }
                low = index + 1;
            } else {
                high = index - 1;
            }
        }
        return res;
    }
};
