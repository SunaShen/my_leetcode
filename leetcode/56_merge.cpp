// @File   : 56_merge.cpp
// @Source : https://leetcode-cn.com/problems/merge-intervals/
// @Title  : 合并区间
// @Auther : sun_ds
// @Date   : 2019/11/19

/**  题目描述：
    给出一个区间的集合，请合并所有重叠的区间。

    示例 1:

    输入: [[1,3],[2,6],[8,10],[15,18]]
    输出: [[1,6],[8,10],[15,18]]
    解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
    示例 2:

    输入: [[1,4],[4,5]]
    输出: [[1,5]]
    解释: 区间 [1,4] 和 [4,5] 可被视为重叠区间。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/merge-intervals
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 给出一个区间的集合，请合并所有重叠的区间。
 *
 * 先排序，后合并
 *  按照区间的 start 大小排序，那么在这个排序的列表中可以合并的区间一定是连续的。
 * 比较tmp的右端点与新区间的左右端点。
 * 若tmp[1]<intervals[i][0].则区间不重合。将tmp放入ans，并tmp=intervals[i]
 * 若tmp[1]>=intervals[i][0]时
 *    tmp[1]<intervals[i][1]，此时有重叠，更新右端点，有tmp[1]=intervals[i][1]
 *    tmp[1]>=intervals[i][1] 此时，tmp覆盖intervals[i]。不需要执行什么操作。
 *
 *  注意最后一次，tmp需要在循环外添加入ans中。
 * 最终返回ans。
 *
 *
 */




class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b){
        if(a[0]==b[0])
            return a[1]>b[1];
        return a[0]<b[0];
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size()==0||intervals.size()==1) return intervals;
        sort(intervals.begin(),intervals.end(),cmp);
        vector<vector<int>> ans;
        vector<int> tmp = intervals[0];
        for(int i=1;i<intervals.size();++i){
            if(tmp[1]>=intervals[i][0]){
                if(tmp[1]<intervals[i][1]){
                    tmp[1] = intervals[i][1];
                }
            }else{
                ans.push_back(tmp);
                tmp = intervals[i];
            }
        }
        ans.push_back(tmp);
        return ans;
    }
};