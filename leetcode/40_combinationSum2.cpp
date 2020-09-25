// @File   : 40_combinationSum2.cpp
// @Source : https://leetcode-cn.com/problems/combination-sum-ii/
// @Title  : 40. 组合总和 II
// @Auther : sun_ds
// @Date   : 2020/9/10

/**  题目描述：
    给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

    candidates 中的每个数字在每个组合中只能使用一次。

    说明：

    所有数字（包括目标数）都是正整数。
    解集不能包含重复的组合。 
    示例 1:

    输入: candidates = [10,1,2,7,6,1,5], target = 8,
    所求解集为:
    [
      [1, 7],
      [1, 2, 5],
      [2, 6],
      [1, 1, 6]
    ]
    示例 2:

    输入: candidates = [2,5,2,1,2], target = 5,
    所求解集为:
    [
      [1,2,2],
      [5]
    ]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/combination-sum-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1.回溯法
 *  针对每个数字 选和不选两种情况。
 *  回溯法
 *
 *  不能包含重复组合。
 *  升序排列。
 *  若当前值等于前一个值，则说明前一次的情况为 10， 当前再选了，情况是 01，重复了，跳过。
 *  剪枝：
 *   假设当前值大于target，则加后面的值更加大于 target，直接 break；
 *
 */

class Solution {
private:
    vector<vector<int>> res;
public:
    void backtrack(vector<int>& candidates, int target, int index, vector<int> temp){
        if(target == 0){
            res.push_back(temp);
            return;
        }
        if(index == candidates.size()) return;
        for(int i=index; i<candidates.size(); i++){
            // 过滤重复 前提(有序)
            // 在当前范围内 [index,size-1]. 若当前值等于前一个值，说明只选当前值的情况与前面重复了，可以跳过。
            // 而至于这两个相同的值都选的情况，则有选中前一个值后递归下去的第一次来选取。因此，上面条件仅对当前范围有作用，即不比较 index 和 index - 1
            if(i-1>=index && candidates[i-1] == candidates[i]) continue;
            // 剪枝 当前值大于 target，后面的一定也大于 target 前提(有序)
            if(target - candidates[i] < 0) break;
            temp.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], i+1, temp);
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        backtrack(candidates, target, 0, {});
        return res;
    }
};
