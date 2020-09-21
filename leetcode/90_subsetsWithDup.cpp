// @File   : 90_subsetsWithDup.cpp
// @Source : https://leetcode-cn.com/problems/subsets-ii/
// @Title  : 子集 II
// @Auther : sun_ds
// @Date   : 2019/11/25

/**  题目描述：
    给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

    说明：解集不能包含重复的子集。

    示例:

    输入: [1,2,2]
    输出:
    [
      [2],
      [1],
      [1,2,2],
      [2,2],
      [1,2],
      []
    ]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/subsets-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/** 序列子集  序列中可能包含重复元素
 *
 * 先排序，使相同的元素处于连续的位置
 *
 * 1.回溯
 *  与不包含重复元素差别只有:
 *  if(i>k+1&&num[i]==num[i-1]) continue;
 * 2.迭代
 *  2.1
 *   使用pre保存上个重复数字对应子集
 *   对于[1,2,2,3]
 *   初始化:
 *   res = [[]]
 *   pre = []
 *   遇到1:
 *   pre:[[],[1]],用res扩展
 *   res:[[],[1]],res = res + pre
 *   遇到2:
 *   pre:[[2],[1,2]],用res扩展
 *   res:[[],[1],[2],[1,2]] res = res + pre
 *   遇到2:
 *   pre: [[2,2],[1,2,2]],用pre扩展
 *   res: [[],[1],[2],[1,2],[2,2],[1,2,2]],res = res + pre
 *   遇到3:
 *   pre:[[3],[1,3],[2,3],[1,2,3],[2,2,3],[1,2,2,3]],用res扩展
 *   res: [[],[1],[2],[1,2],[2,2],[1,2,2],[3],[1,3],[2,3],[1,2,3],[2,2,3],[1,2,2,3]],res = res + pre
 *
 *   即当前值和前面值一样，用pre扩展，否则使用res扩展
 *  2.2 统计次数
 *   当有 n 个重复数字出现，其实就是在出现重复数字之前的所有解中，分别加 1 个重复数字， 2 个重复数字，3 个重复数字
 *   数组 [ 1 2 2 2 ]
 *   [ ]的所有子串 [ ]
 *   [ 1 ] 个的所有子串 [ ] [ 1 ]
 *   然后出现了重复数字 2，那么我们记录重复的次数。然后遍历之前每个解即可
 *   对于 [ ] 这个解，
 *   加 1 个 2，变成 [ 2 ]
 *   加 2 个 2，变成 [ 2 2 ]
 *   加 3 个 2，变成 [ 2 2 2 ]
 *   对于 [ 1 ] 这个解
 *   加 1 个 2，变成 [ 1 2 ]
 *   加 2 个 2，变成 [ 1 2 2 ]
 *   加 3 个 2，变成 [ 1 2 2 2 ]
 *
 *   最终结果: [[],[1],[1,2],[1,2,2],[1,2,2,2],[2],[2,2],[2,2,2]]
 *
 *   for循环中统计重复元素次数，累加上去
 *
 *  3.位掩码
 *
 *  区别于之前，怎么去除重复的。
 *
 * 二进制对应数字     1       2       2       对应子集    是否选用
 *      0           0       0       0       []            1
 *      1           0       0       1       [2]           0
 *      2           0       1       0       [2]           1
 *      3           0       1       1       [2,2]         1
 *      4           1       0       0       [1]           1
 *      5           1       0       1       [1,2]         0
 *      6           1       1       0       [1,2]         1
 *      7           1       1       1       [1,2,2]       1
 *
 *      判断是否选用条件，if(j>0&&nums[j]==nums[j-1]&&(i>>(j-1)&1)==0)满足，不使用
 *      该判断条件意思为，当前位与前一位数字相同，并且前一位二进制0(当前二进制肯定为1，否则进不了上一次if).
 *      即对与[2,2,2,2]序列
 *      下面重复情况，只选取一个，即第一个。对应上面条件。:
 *      [1,1,0,0]  [2,2]
 *      [1,0,1,0]  [2,2]
 *      [1,0,0,1]  [2,2]
 *      [0,1,1,0]  [2,2]
 *      [0,1,0,1]  [2,2]
 *      [0,0,1,1]  [2,2]
 */

//递归 回溯
class Solution {
private:
    vector<vector<int>> ans;
    int n;
public:
    void func(int k,vector<int> temp,vector<int> num){

        // if(k == n){
        //     ans.push_back(temp);
        //     return;
        // }

        // 子集问题，记录整个路径
        ans.push_back(temp);
        // 子集问题，不考虑顺序，(组合考虑顺序)，因此用过的就丢了，i 从 k 开始
        for(int i=k;i<n;++i){
            if(i>k&&num[i]==num[i-1]) continue;
            temp.push_back(num[i]);
            func(i+1,temp,num);
            temp.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        n = nums.size();
        sort(nums.begin(),nums.end());
        func(0,{},nums);
        return ans;
    }
};



//迭代
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans{{}};
        int start = 0;
        for(int i=0;i<n;++i){
            int len = ans.size();
            // 新数字，全部遍历
            if(i>0&&nums[i]!=nums[i-1])
                start = 0;
            for(int j=start;j<len;++j){
                vector<int> temp = ans[j];
                temp.push_back(nums[i]);
                ans.push_back(temp);
            }
            // 重复数字,从上一轮新添加的部分开始
//            start = ans.size() - len + start;
            star = len;
        }
        return ans;
    }
};

//统计次数
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans{{}};
        for(int i=0;i<n;++i){
            int len = ans.size();
            int dup_num = 0;
            //关键 取i+1 用i与i+1比，从第一个重复的就开始了
            while(((i+1)<n)&&nums[i]==nums[i+1]){
                ++dup_num;
                ++i;
            }
            for(int j=0;j<len;++j){
                vector<int> temp = ans[j];
                //关键 等号 [0,dup_num]
                //没有重复时，dup_num=0，执行一次。
                for(int k=0;k<=dup_num;++k){
                    //此时nums[i]为重复序列的最后一个。因为有++i。
                    temp.push_back(nums[i]);
                    ans.push_back(temp);
                }
            }
        }
        return ans;
    }
};

//位掩码
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();
        long N = 1<<n;
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans;
        for(long i=0;i<N;++i){
            vector<int> temp;
            bool flag = true;
            for(int j=0;j<n;++j){
                if(i>>j&1){
                    if(j>0&&nums[j]==nums[j-1]&&(i>>(j-1)&1)==0){
                        flag = false;
                        break;
                    }else{
                        temp.push_back(nums[j]);
                    }
                }
            }
            if(flag){
                ans.push_back(temp);
            }
        }
        return ans;
    }
};