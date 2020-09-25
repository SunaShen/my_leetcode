// @File   : 216_combinationSum3.cpp
// @Source : https://leetcode-cn.com/problems/combination-sum-iii/
// @Title  : 216. 组合总和 III
// @Auther : sun_ds
// @Date   : 2020/9/11

/**  题目描述：
    找出所有相加之和为 n 的 k 个数的组合。组合中只允许含有 1 - 9 的正整数，并且每种组合中不存在重复的数字。

    说明：

    所有数字都是正整数。
    解集不能包含重复的组合。 
    示例 1:

    输入: k = 3, n = 7
    输出: [[1,2,4]]
    示例 2:

    输入: k = 3, n = 9
    输出: [[1,2,6], [1,3,5], [2,3,4]]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/combination-sum-iii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.回溯法
 * 终止条件元素数量必须为 k 个。
 *
 * 使用 target - candidates[i] < 0 剪枝。
 *
 *
 *
 */

class Solution {
private:
    vector<vector<int>> res;
public:
    void backtrack(vector<int>& candidates, int target, int index, vector<int> temp, int k){
        if(temp.size() > k) return;
        if(target == 0){
            if(temp.size() == k)
                res.push_back(temp);
            return;
        }
        if(index == candidates.size()) return;
        for(int i=index; i<candidates.size(); i++){
            if(target - candidates[i] < 0) break;
            temp.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], i+1, temp, k);
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> candidates = {1,2,3,4,5,6,7,8,9};
        backtrack(candidates, n, 0, {}, k);
        return res;
    }
};

