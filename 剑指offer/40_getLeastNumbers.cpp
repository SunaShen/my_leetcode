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
 *  建堆复杂度 O(N)
 *  时间复杂度度 O(N)
 *  空间复杂度 O(N)
 *
 * 2.大顶堆
 *  构建 k 大小的大顶堆
 *  遍历所有数字，若小于堆顶则堆顶出堆，并将该数字放入堆中，最终堆中的 k 个数为结果
 *
 *  时间复杂度 O(NlogK)
 *  空间复杂度 O(K)
 *
 * 3.快排思想
 *  如果partition<k 则，partition前的数都是前k小。左边界从partition+1开始找剩下的
 *  如果partition>k 则，右边界变到partition-1，继续寻找。
 * 直到找到k个值。
 *
 * 时间复杂度 O(N)
 * 空间复杂度 O(logN)
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

class Solution {
public:
    int partiation(vector<int>& nums, int l, int r){
        int i = l;
        int j = l;
        while(j < r){
            if(nums[j] < nums[r]){
                swap(nums[i], nums[j]);
                i++;
            }
            j++;
        }
        swap(nums[i], nums[r]);
        return i;
    }
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        if (k==0) return {};
        int l = 0, r = arr.size()-1;
        while(true){
            int q = partiation(arr, l, r);
            // 与 k-1 比较 第 1 小对应索引为 0
            if(q > (k-1)){
                r = q - 1;
            }else if(q == (k-1)){
                break;
            }else{
                l = q + 1;
            }
        }
        return vector<int>(arr.begin(), arr.begin()+k);
    }
};

class Solution {
public:
    int pratition(vector<int>& num,int l,int r){
        int i=l;
        for(int j=l;j<r;j++){
            if(num[j]<num[r]){
                swap(num[j],num[i]);
                i++;
            }
        }
        swap(num[i],num[r]);
        return i;
    }
    void search(vector<int>& arr, int k, int l, int r){
        if(l>=r) return;
        int p = pratition(arr,l,r);
        if(p==k-1) return;
        else if(p<k) search(arr,k,p+1,r);
        else search(arr,k,l,p-1);
    }
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        if(k==0) return {};
        search(arr,k,0,arr.size()-1);
        return vector<int>(arr.begin(),arr.begin()+k);
    }
};