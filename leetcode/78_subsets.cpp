// @File   : 78_subsets.cpp
// @Source : https://leetcode-cn.com/problems/subsets/
// @Title  : 子集
// @Auther : sun_ds
// @Date   : 2019/11/23

/**  题目描述：
    给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

    说明：解集不能包含重复的子集。

    示例:

    输入: nums = [1,2,3]
    输出:
    [
      [3],
      [1],
      [2],
      [1,2,3],
      [1,3],
      [2,3],
      [1,2],
      []
    ]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/subsets
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/** 求序列的所有子集
 * n个不重复的数的子集个数 C(n,0)+C(n,1)+......+C(n,n-2)+C(n,n-1)+C(n,n) = 2^n个。
 *
 * 1.回溯 O(n!)
 *  递归函数func(i,temp,num)
 *  i为当前访问数组下标，temp为中间结果，num为原始序列
 *  当i==n,遍历完所有,return
 *  将temp加入结果ans中，ans.push_back(temp)
 *  遍历剩下的数组，进行回溯，j=[i+1,n]
 *      在temp后面添加nums[j]
 *      func(j,temp,num)
 *      恢复之前temp,temp.pop_back(),供下一次遍历使用
 *
 *  调用func，func(-1,{},nums)
 *  返回结果，return ans;
 *
 * 2.迭代 O(n!)
 *   对于[1,2,3]
 *   初始化 ans = [[]]
 *   遇到1：
 *   [1]
 *   ans = [[],[1]]
 *   遇到2:
 *   [2]
 *   [1,2]
 *   ans = [[],[1],[2],[1,2]]
 *   遇到3:
 *   [3]
 *   [1,3]
 *   [2,3]
 *   [1,2,3]
 *   ans = [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 *
 *   最终结果 ans
 *
 *   for(int i=0;i<n;i++)
 *      int m = ans.size();
 *      for(int j=0;j<m;++j)
 *
 *
 * 3.位掩码 O(n*2^n)
 * 精妙
 * 将对应子集的索引转换到二进制
 *
 * 二进制对应数字     1       2       3       对应子集
 *      0           0       0       0       []
 *      1           0       0       1       [3]
 *      2           0       1       0       [2]
 *      3           0       1       1       [2,3]
 *      4           1       0       0       [1]
 *      5           1       0       1       [1,3]
 *      6           1       1       0       [1,2]
 *      7           1       1       1       [1,2,3]
 *
 * n为序列长度
 * 取数字[0,2^n]的二进制，二进制各个位上0和1代表当前子集中是否选取该元素
 *
 *
 *
 */


//回溯法
//O(n!)
class Solution {
public:
    vector<vector<int>> ans;
    int n;
    void func(int i, vector<int> temp, vector<int> num){
        if(i==n)
            return;
        ans.push_back(temp);
        //核心，剪枝
        for(int j=i+1;j<n;++j){
            temp.push_back(num[j]);
            func(j,temp,num);
            temp.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        n = nums.size();
        func(-1,{},nums);
        return ans;
    }
};

//迭代
//O(n!)
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> ans{{}};
        for(int i=0;i<n;i++){
            int m = ans.size();
            for(int j=0;j<m;++j){
                vector<int> temp = ans[j];
                temp.push_back(nums[i]);
                ans.push_back(temp);
            }
        }
        return ans;
    }
};

//位掩码
//O(n*2^n)
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        long N = 1<<n;
        vector<vector<int>> ans;
        for(long i=0;i<N;++i){
            vector<int> temp;
            for(int j=0;j<n;++j){
                if(i>>j&1){
                    temp.push_back(nums[j]);
                }
            }
            ans.push_back(temp);
        }
        return ans;
    }
};