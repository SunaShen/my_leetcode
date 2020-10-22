// @File   : 763_partitionLabels.cpp
// @Source : https://leetcode-cn.com/problems/partition-labels/
// @Title  : 763. 划分字母区间
// @Auther : sun_ds
// @Date   : 2020/10/22

/**  题目描述：
    字符串 S 由小写字母组成。我们要把这个字符串划分为尽可能多的片段，同一个字母只会出现在其中的一个片段。返回一个表示每个字符串片段的长度的列表。

     

    示例 1：

    输入：S = "ababcbacadefegdehijhklij"
    输出：[9,7,8]
    解释：
    划分结果为 "ababcbaca", "defegde", "hijhklij"。
    每个字母最多出现在一个片段中。
    像 "ababcbacadefegde", "hijhklij" 的划分是错误的，因为划分的片段数较少。
     

    提示：

    S的长度在[1, 500]之间。
    S只包含小写字母 'a' 到 'z' 。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/partition-labels
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 贪心 + 双指针
 *  首先遍历字符串，获得各个字符出现的最大下标
 *  再次遍历字符串，维护 start，end 分段，使用各个字符出现的最大下标更新 end。
 *  当遍历到 i == end 时，表示该分段可以单独分段，记录该分段长度 end - start + 1. 并令 start = end + 1,继续遍历。
 *
 *  时间复杂度 O(N)
 *  空间复杂度 O(n) n=26个字符
 *
 */

class Solution {
public:
    vector<int> partitionLabels(string S) {
        // 记录每个字符出现的最大索引
        vector<int> right(26, 0);
        for(int i=0;i<S.size();i++){
            right[S[i] - 'a'] = i;
        }
        vector<int> res;
        int start = 0, end = 0;
        for(int i=0;i<S.size();i++){
            end = max(end, right[S[i] - 'a']);
            if(i == end){
                res.push_back(end - start + 1);
                start = end + 1;
                // end 自己会增加的，由于end = max(end, right[S[i] - 'a']);
            }
        }
        return res;
    }
};
