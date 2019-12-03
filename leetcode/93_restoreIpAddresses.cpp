// @File   : 93_restoreIpAddresses.cpp
// @Source : https://leetcode-cn.com/problems/restore-ip-addresses/
// @Title  : 复原IP地址
// @Auther : sun_ds
// @Date   : 2019/11/6

/*  题目描述：
    给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。

    示例:

    输入: "25525511135"
    输出: ["255.255.11.135", "255.255.111.35"]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/restore-ip-addresses
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
 * 复原IP地址
 *
 * 回溯法
 * 1.结束条件
 * 2.循环
 * 3.满足条件，记录，继续递归
 *
 * IP地址约束：
 * 1.必须刚好四段
 * 2.每一段范围[0,255]
 * 3.注意处理连续的0，即每个0字符只能成一段
 *
 * 结束条件:有四段了并且字符串刚好用完
 * 循环:段长度1~3
 * 约束条件:当前段在[0,255]之间，记录，继续递归
 *
 * 输入参数：b当前段起始位置 t为当前为第几段
 *
 *
 */


#include <iostream>
#include <vector>
#include <array>
#include <string>


using namespace std;

class Solution {
public:
    vector<string> ans;
    string as;
    array<string,4> a;
    //b当前段起始位置 t为当前为第几段
    void func(int b,int t){
        if(t==4) {
            if(b==as.size())
                ans.push_back(a[0] + '.' + a[1] + '.' + a[2] + '.' + a[3]);
            else
                return ;
        }
        int temp = 0;
        if(as[b]=='0'){
            a[t] = to_string(0);
            func(b+1,t+1);
        }else{
            for(int i=b;i<b+3&&i<as.size();++i){
                temp = temp * 10 + as[i] - '0';
                if(temp>255) continue;
                a[t] = to_string(temp);
                func(i+1,t+1);
            }
        }

        return ;
    }
    vector<string> restoreIpAddresses(string s) {
        as = s;

        func(0,0);

        return ans;
    }
};

int main(int argc, char * argv[])
{
    string s = "010010";
    Solution su;
    auto res = su.restoreIpAddresses(s);
    for(auto k : res)
        cout << k << endl;

    return 0;
}