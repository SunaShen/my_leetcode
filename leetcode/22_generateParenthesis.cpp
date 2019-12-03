// @File   : 22_generateParenthesis.cpp
// @Source : https://leetcode-cn.com/problems/generate-parentheses/
// @Title  : 括号生成
// @Auther : sun_ds
// @Date   : 2019/11/7

/*  题目描述：
    给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。

    例如，给出 n = 3，生成结果为：

    [
      "((()))",
      "(()())",
      "(())()",
      "()(())",
      "()()()"
    ]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/generate-parentheses
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
 * 括号生成
 *
 * 括号生成规则：
 * 1.左括号数=右括号数=n 若有超过n可剪枝
 * 2.从左往右，实时左括号数要大于等于右括号数。。。。且当左括号数等于右括号时，只能后面添加左括号。剪枝右括号。
 *
 * 回溯法需要返回结果的，需要保存中间结果。
 * 1.使用全局变量，进入下一层push_back,return回来恢复pop_back
 * 2.使用形参，每一层递归会保存自己的状态
 *
 *
 *
 * 善用剪枝！！！利用特征。
 *
 */




#include <iostream>
#include <vector>
#include <string>



using namespace std;

//class Solution {
//public:
//    vector<string> ans;
//    string p;
//    int N = 0;
//    int cnt[2] = {0,0};
//    void func(int k){
//        //剪枝 左右括号数不能大于N，且左括号数必须大于等于右括号数
//        if(cnt[0] > N||cnt[1] > N || cnt[0] < cnt[1]){
//            return;
//        }
//        //k记录了所有的括号数。
//        if(k==0){
//            //左右括号数相等符合要求。
//            if(cnt[0]==cnt[1]){
//                ans.push_back(p);
//            }else{
//                return;
//            }
//        }
//
//        ++cnt[0];
//        p.push_back('(');
//        func(k-1);
//        p.pop_back();
//        --cnt[0];
//
//        ++cnt[1];
//        p.push_back(')');
//        func(k-1);
//        p.pop_back();
//        --cnt[1];
//
//    }
//    vector<string> generateParenthesis(int n) {
//        N = n;
//        func(2*n);
//        return ans;
//    }
//};




//class Solution {
//public:
//    void pushBracket(vector<string>& res, string cur, int open, int close, int n) {
//        if(close==n)  res.push_back(cur);
//        else if(open==n) {
//            pushBracket(res, cur+')', open, close+1, n);
//        }
//        else if(open==close) {
//            pushBracket(res, cur+'(', open+1, close, n);
//        } else {
//            pushBracket(res, cur+'(', open+1, close, n);
//            pushBracket(res, cur+')', open, close+1, n);
//        }
//    }
//    vector<string> generateParenthesis(int n) {
//        vector<string> res;
//        pushBracket(res, "", 0, 0, n);
//        return res;
//    }
//};


//剪枝剪得干干净净。
class Solution {
public:
    vector<string> ans;
    void back_track(string cur,int open,int close,int m){
        //由判断条件保证open，close都小于等于m。故当满足cur.size()==m*2时，只有open=close=m，即满足条件
        if (cur.size()== m * 2) {
            ans.push_back(cur);
            return;
        }
        if (open<m)
            back_track(cur+"(", open+1, close, m);
        if (close<open)
            back_track(cur+")", open, close+1, m);
    }
    vector<string> generateParenthesis(int n) {
        back_track("",0,0,n);
        return ans;
    }
};



int main(int argc, char * argv[])
{
    Solution su;
    auto res = su.generateParenthesis(3);
    for(auto k : res){
        cout << k << endl;
    }
    return 0;
}


