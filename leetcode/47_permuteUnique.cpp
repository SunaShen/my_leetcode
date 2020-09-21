// @File   : 47_permuteUnique.cpp
// @Source : https://leetcode-cn.com/problems/permutations-ii/
// @Title  : 47. 全排列 II
// @Auther : sun_ds
// @Date   : 2019/11/8

/**  题目描述：
    给定一个可包含重复数字的序列，返回所有不重复的全排列。

    示例:

    输入: [1,1,2]
    输出:
    [
      [1,1,2],
      [1,2,1],
      [2,1,1]
    ]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/permutations-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 全排列II
 * 给定一个<可包含重复>数字的序列，返回所有不重复的全排列
 *
 * 1. 回溯法
 * 全排列要考虑顺序的，考虑情况，选中后面数字之后在选中前面数字，因此每次循环的范围为[0,n-1]，而不是值搜索后半部分。
 * for循环遍历 [0,n-1]
 *   选中某数字，temp存储该数字
 *   递归
 *   恢复该数字，temp删除该数字
 *
 * 数组中有重复数字，因此，先将数组排序(相同的值是相邻的)
 * 然后 在 for 循环时判断 (i > 0 && nums[i] == nums[i-1] && !used[i-1])
 * 其中 nums[i] == nums[i-1] 表示当前值之前也出现过
 * !used[i-1] 表示在此之前 前面和自己相同的值没有被用(潜台词，可能以后被用，那么这样必然和先用前面再用自己形成重复，需要剪枝)
 *
 *
 * 2. 回溯法 使用 map
 * 使用 map 统计各个数出现的次数
 *
 * 严格控制每一层遍历只能取该数字一次，然后下一层递归从剩下的数字里面选择。
 * 这样保证了不会出现重复的情况。
 *
 *
 */

class Solution {
private:
    vector<vector<int>> res;
public:
    void dfs(vector<int>& nums, vector<bool>& used, vector<int>& temp){
        if(temp.size() == nums.size()){
            res.push_back(temp);
            return;
        }
        // 不像 全排列(不包含重复元素) 可以用 swap
        for(int i = 0; i < nums.size(); i++){
            if(!used[i]){
                if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
                temp.push_back(nums[i]);
                used[i] = true;
                dfs(nums, used, temp);
                used[i] = false;
                temp.pop_back();
            }
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        vector<bool> used(n, false);
        vector<int> temp;
        func(nums, used, temp);
        return res;
    }
};

class Solution {
private:
    vector<vector<int>> res;
    int n;
public:
    void func(map<int, int>& m, vector<int>& temp){
        if(temp.size()==n){
            res.push_back(temp);
            return;
        }
        // 同层 同一个值只能取一次
        for(auto &i:m){
            if(i.second){
                --i.second;
                temp.push_back(i.first);
                func(m);
                temp.pop_back();
                ++i.second;
            }
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        n = nums.size();
        map<int, int> m;
        vector<int> temp;
        for (int i : nums) ++m[i];
        func(m, temp);
        return res;
    }
};
