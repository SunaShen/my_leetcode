// @File   : 47_permuteUnique.cpp
// @Source : https://leetcode-cn.com/problems/permutations-ii/
// @Title  : 全排列 II
// @Auther : sun_ds
// @Date   : 2019/11/8

/*  题目描述：
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

/*
 * 全排列II
 * 给定一个<可包含重复>数字的序列，返回所有不重复的全排列
 *
 * 回溯法
 * for循环遍历各不重复数字(排序后，跳过相同的，实现不重复)
 * 删除该数字，结果存储该数字
 * 递归
 * 恢复该数字，结果删除该数字
 *
 * 直到结果长度等于数字的size结束并保存。
 *
 *
 * 结果可以用vector<int>保存，使用push_back和pop_back
 * 当前搜索数字使用vector<int>。需要使用eras和insert。vector在除了末尾以外的地方插入和删除速度较慢
 *
 *
 * 技巧：
 * 使用map代替vector<int>。索引值为数字值，值为该值出现的次数，还省去了去重的步骤。
 * 删除该数字即该数字对应的值减一。恢复该数字，即加一。
 *
 *
 *
 *
 *
 *
 */

#include <iostream>
#include <vector>
#include <map>



using namespace std;


//class Solution {
//public:
//    vector<vector<int>> ans;
//    vector<int> cun;
//    void func(vector<int> num){
//        if(num.empty()){
//            ans.push_back(cun);
//            return;
//        }
//        for(int i=0;i<num.size();++i){
//            if(i>0&&num[i]==num[i-1]) continue;
//            cun.push_back(num[i]);
//            num.erase(num.begin()+i);
//            func(num);
//            num.insert(num.begin()+i,cun.back());
//            cun.pop_back();
//        }
//    }
//    vector<vector<int>> permuteUnique(vector<int>& nums) {
//        sort(nums.begin(),nums.end());
//        func(nums);
//        return ans;
//    }
//};

class Solution {
public:
    vector<vector<int>> ans;
    vector<int> cun;
    int n;
    void func(map<int, int>& m){
        if(cun.size()==n){
            ans.push_back(cun);
            return;
        }
        for(auto &i:m){
            if(i.second){
                --i.second;
                cun.push_back(i.first);
                func(m);
                cun.pop_back();
                ++i.second;
            }
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        n = nums.size();
        map<int, int> m;
        for (int i : nums) ++m[i];
        func(m);
        return ans;
    }
};


int main(int argc, char * argv[])
{
    vector<int> mm{1,1,2};
    Solution su;
    auto res = su.permuteUnique(mm);
    for(auto k : res){
        for(auto m : k){
            cout << m << " ";
        }
        cout << endl;
    }
    return 0;
}


