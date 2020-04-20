// @File   : 59-1_maxSlidingWindow.cpp
// @Source : https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/
// @Title  : 面试题59 - I. 滑动窗口的最大值
// @Auther : sun_ds
// @Date   : 2020/3/29

/**  题目描述：
    给定一个数组 nums 和滑动窗口的大小 k，请找出所有滑动窗口里的最大值。

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

    你可以假设 k 总是有效的，在输入数组不为空的情况下，1 ≤ k ≤ 输入数组的大小。

    注意：本题与主站 239 题相同：https://leetcode-cn.com/problems/sliding-window-maximum/



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof
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



