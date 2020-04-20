// @File   : 239_maxSlidingWindow.cpp
// @Source : https://leetcode-cn.com/problems/sliding-window-maximum/
// @Title  : 239. 滑动窗口最大值
// @Auther : sun_ds
// @Date   : 2020/3/29

/**  题目描述：
    给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

    返回滑动窗口中的最大值。

     

    进阶：

    你能在线性时间复杂度内解决此题吗？

     

    示例:

    输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
    输出: [3,3,5,5,6,7]
    解释:

      滑动窗口的位置                最大值
    ---------------               -----
    [1  3  -1] -3  5  3  6  7       3
     1 [3  -1  -3] 5  3  6  7       3
     1  3 [-1  -3  5] 3  6  7       5
     1  3  -1 [-3  5  3] 6  7       5
     1  3  -1  -3 [5  3  6] 7       6
     1  3  -1  -3  5 [3  6  7]      7
     

    提示：

    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4
    1 <= k <= nums.length


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/sliding-window-maximum
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 滑动窗口中的最大值
 * 1.队列
 * 维护单调递减队列
 * 队头为当前窗口中最大值。
 *
 *
 */


class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        if(n==0) return {};
        vector<int> res;
        deque<int> q;
        int i=0;
        for(;i<k;i++){
            while(!q.empty()&&q.back()<nums[i]){
                q.pop_back();
            }
            q.push_back(nums[i]);
        }
        res.push_back(q.front());
        for(;i<n;i++){
            if(nums[i-k]==q.front()){
                q.pop_front();
            }
            while(!q.empty()&&q.back()<nums[i]){
                q.pop_back();
            }
            q.push_back(nums[i]);
            res.push_back(q.front());
        }
        return res;
    }
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        if(n==0) return {};
        vector<int> res;
        deque<int> q;
        for(int i=0;i<n;i++){
            while(!q.empty()&&nums[q.back()]<nums[i]){ //维持递减队列
                q.pop_back();
            }
            if(!q.empty()&&q.front()<=i-k) q.pop_front(); //窗口移动，使得最大值出去了
            q.push_back(i);
            if(i>=k-1) res.push_back(nums[q.front()]); //保存当前最大值
        }
        return res;
    }
};

