// @File   : 46_permute.cpp
// @Source : https://leetcode-cn.com/problems/permutations/
// @Title  : 全排列
// @Auther : sun_ds
// @Date   : 2019/11/8

/*  题目描述：
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


/*

 *
 * 全排列
 * 给定一个<没有重复>数字的序列，返回其所有可能的全排列。
 *
 * 回溯法
 * for循环遍历各不重复数字
 * 删除该数字，结果存储该数字
 * 递归
 * 恢复该数字，结果删除该数字
 *
 * 直到结果长度等于数字的size结束并保存。
 *
 *
 * 结果可以用vector<int>保存，使用push_back和pop_back
 * 当前搜索数字使用vector<int>。需要使用erase和insert。vector在除了末尾以外的地方插入和删除速度较慢
 *
 *
 *
 * 使用swap(num[cnt],num[i]);而不是erase和insert。使用过的就换到前面。
 * 然后每一次从下一层开始cnt+1，cnt为层数。
 * 当cnt==num.size()说明遍历到了叶节点。
 * 存储。ans.push_back(num)
 * 返回后，恢复再使用swap(num[cnt],num[i]);
 *
 * 省去了erase和insert，且不用使用单独开辟记录vector<int> cun。当前num就是当前排列。
 *
 *
 *
 * 本题使用map没啥必要。
 * 技巧：
 * 使用map代替vector<int>。索引值为数字值，值为该值出现的次数
 * 删除该数字即该数字对应的值减一。恢复该数字，即加一。
 *
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

//class Solution {
//public:
//    vector<vector<int>> ans;
//    vector<int> cun;
//    int n;
//    void func(map<int, int>& m){
//        if(cun.size()==n){
//            ans.push_back(cun);
//            return;
//        }
//        for(auto &i:m){
//            if(i.second){
//                --i.second;
//                cun.push_back(i.first);
//                func(m);
//                cun.pop_back();
//                ++i.second;
//            }
//        }
//    }
//    vector<vector<int>> permute(vector<int>& nums) {
//        n = nums.size();
//        map<int, int> m;
//        for (int i : nums) ++m[i];
//        func(m);
//        return ans;
//    }
//};

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
        sort(nums.begin(),nums.end());
        func(nums,0);
        return ans;
    }
};



int main(int argc, char * argv[])
{
    vector<int> mm{1,2,3};
    Solution su;
    auto res = su.permute(mm);
    for(auto k : res){
        for(auto m : k){
            cout << m << " ";
        }
        cout << endl;
    }
    return 0;
}
