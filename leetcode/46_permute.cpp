// @File   : 46_permute.cpp
// @Source : https://leetcode-cn.com/problems/permutations/
// @Title  : 46. 全排列
// @Auther : sun_ds
// @Date   : 2019/11/8

/**  题目描述：
    给定一个没有重复数字的序列，返回其所有可能的全排列。

    示例:

    输入: [1,2,3]
    输出:
    [
      [1,2,3],
      [1,3,2],
      [2,1,3],
      [2,3,1],
      [3,1,2],
      [3,2,1]
    ]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/permutations
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 全排列
 * 给定一个<没有重复>数字的序列，返回其所有可能的全排列。
 *
 * 1. 回溯法
 * 全排列要考虑顺序的，考虑情况，选中后面数字之后在选中前面数字，因此每次循环的范围为[0,n-1]，而不是值搜索后半部分。
 * for循环遍历 [0,n-1]
 *   选中某数字，temp存储该数字
 *   递归
 *   恢复该数字，temp删除该数字
 *
 * 直到temp长度等于数字的size结束并保存。使用 vector<bool> used 存储该元素是否选中
 *
 * 2. 回溯法 使用 swap
 * 使用 swap 每次将选中的元素放置前面，那么接下来搜索的范围为后半部分。
 * for 循环的搜索区间为 [cnt, n-1]
 * 最终 cnt == n时，保存 nums 即为结果。
 *
 * for循环遍历 [cnt,n-1]
 *   选中某数字，swap 到前面
 *   递归
 *   恢复该数字，swap 回来
 *
 *
 */

class Solution {
private:
    vector<vector<int>> ans;
public:
    void func(vector<int>& nums, vector<bool>& used, vector<int>& temp){
        if(temp.size() == nums.size()){
            ans.push_back(temp);
            return;
        }
        // 全排列 需要顺序的。可能选了后面的再选前面的，因此[0,n-1]都得遍历，使用 used 记录用过的。
        // 不同于 子集， 不区分顺序，每次只考虑后半部分
        // 也可以用 swap 来节省空间，转换成只考虑后半部分
        for(int i = 0;i < nums.size(); ++i){
            if(!used[i]){
                temp.push_back(nums[i]);
                used[i] = true;
                func(nums, used, temp);
                used[i] = false;
                temp.pop_back();
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        vector<bool> used(n, false);
        vector<int> temp;
        func(nums, used, temp);
        return ans;
    }
};


class Solution {
public:
    vector<vector<int>> ans;
    void func(vector<int> num,int cnt){
        if(cnt == num.size()){
            ans.push_back(num);
            return;
        }
        for(int i=cnt;i<num.size();++i){
            swap(num[cnt],num[i]);
            func(num,cnt+1);
            swap(num[cnt],num[i]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        func(nums,0);
        return ans;
    }
};
