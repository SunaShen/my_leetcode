// @File   : 39_combinationSum.cpp
// @Source : https://leetcode-cn.com/problems/combination-sum/
// @Title  : 39. 组合总和
// @Auther : sun_ds
// @Date   : 2020/9/9

/**  题目描述：
    给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

    candidates 中的数字可以无限制重复被选取。

    说明：

    所有数字（包括 target）都是正整数。
    解集不能包含重复的组合。 
    示例 1：

    输入：candidates = [2,3,6,7], target = 7,
    所求解集为：
    [
      [7],
      [2,2,3]
    ]
    示例 2：

    输入：candidates = [2,3,5], target = 8,
    所求解集为：
    [
      [2,2,2,2],
      [2,3,3],
      [3,5]
    ]
     

    提示：

    1 <= candidates.length <= 30
    1 <= candidates[i] <= 200
    candidate 中的每个元素都是独一无二的。
    1 <= target <= 500

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/combination-sum
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 回溯法
 *  遍历各个元素。
 *
 *  每个元素有选和不选两种状态
 *  当前轮次从 index 后面选一个元素。
 *  回溯写法：
 *  for (int i=index; i<size; i++)
 *      temp.push_back(nums[i])
 *      dfs(i+1)
 *      temp.pop_back()
 *
 *  当前每个元素可以选择无数次，因此将 dfs(i+1) 改为 dfs(i) 即可。
 *
 *  结束条件：
 *  每选中一个元素，target - nums[i]. 因此 target == 0 时，递归结束，记录。或者 target < 0，不符合要求，递归结束
 *
 *  使用 target减， 不用多一个变量记录 sum。
 *
 *  剪枝
 *  各元素升序排列。
 *  当前 target  - nums[i] < 0; 那么后面的元素也必定 < 0。直接 break，跳出循环(后面不需要遍历了)。
 *
 */

class Solution {
private:
    vector<vector<int>> res;
public:
    void backtrack(vector<int>& candidates, int target, int index, int sum, vector<int> temp){
        if(sum == target){
            res.push_back(temp);
            return;
        }
        if(sum > target) return;
        for(int i=index;i<candidates.size();i++){
            vector<int> t(temp);
            int s = sum;
            while(s+candidates[i] <= target){
                s += candidates[i];
                t.push_back(candidates[i]);
                backtrack(candidates, target, i+1, s, t);
            }
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backtrack(candidates, target, 0, 0, {});
        return res;
    }
};


class Solution {
private:
    vector<vector<int>> res;
public:
    void backtrack(vector<int>& candidates, int target, int index, vector<int>& temp){
        if(target == 0){
            res.push_back(temp);
            return;
        }
        for(int i = index; i < candidates.size(); i++){
            // 剪枝 candidates 升序排列。 当前选择candidates[i]已经超过 target 了，后面的就更没必要了。
            if (target - candidates[i] < 0) {
                break;
            }
            temp.push_back(candidates[i]);
            // index 还是 i, 下次还可以选当前元素。
            backtrack(candidates, target - candidates[i], i, temp);
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> temp;
        backtrack(candidates, target, 0, temp);
        return res;
    }
};