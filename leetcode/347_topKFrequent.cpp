// @File   : 347_topKFrequent.cpp
// @Source : https://leetcode-cn.com/problems/top-k-frequent-elements/
// @Title  : 前 K 个高频元素
// @Auther : sun_ds
// @Date   : 2019/12/16

/**  题目描述：
    给定一个非空的整数数组，返回其中出现频率前 k 高的元素。

    示例 1:

    输入: nums = [1,1,1,2,2,3], k = 2
    输出: [1,2]
    示例 2:

    输入: nums = [1], k = 1
    输出: [1]
    说明：

    你可以假设给定的 k 总是合理的，且 1 ≤ k ≤ 数组中不相同的元素的个数。
    你的算法的时间复杂度必须优于 O(n log n) , n 是数组的大小。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/top-k-frequent-elements
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 1.哈希+排序
 *  使用unordered_map存储各数出现的次数。
 *  将map按照值降序排序，取前k个键值对的键值即为结果
 *
 *  只有有序容器支持sort，利用pair将map转为vector排序。
 *
 *  使用map存储，复杂度O(n)，排序复杂度O(nlogn)
 *  故复杂度为O(nlogn)
 *
 * 2.哈希+小顶堆
 *  使用unordered_map存储各数出现的次数。
 *  构建小顶堆。将各键值对pair依次加入该堆中，当堆中元素超过k时，pop。
 *  最终，使得堆中元素即为所求。
 *
 *
 *
 */


class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> m;
        for(int i=0;i<nums.size();++i){
            m[nums[i]]++;
        }
        vector<int> ans;
        vector<pair<int,int>> temp(m.begin(),m.end());
        sort(temp.begin(),temp.end(),
             [](const pair<int,int> &a,const pair<int,int> &b){return a.second>b.second;});
        auto iter = temp.begin();
        for(int i=0;i<k;++i){
            ans.push_back(iter->first);
            iter++;
        }
        return ans;
    }
};


class Solution {
public:
    struct cmp{
        bool operator()(const pair<int,int> &a, const pair<int,int> &b){return a.second > b.second;};
    };
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> m;
        for(auto i:nums){
            m[i]++;
        }
        //小顶堆
        priority_queue<pair<int,int>,vector<pair<int,int>>,cmp> pri;
        for(auto i:m){
            pri.push(i);
            if(pri.size()>k)
                pri.pop();
        }
        vector<int> ans;
        while(!pri.empty()){
            ans.push_back(pri.top().first);
            pri.pop();
        }
        return ans;
    }
};