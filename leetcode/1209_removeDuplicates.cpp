// @File   : 1209_removeDuplicates.cpp
// @Source : https://leetcode-cn.com/problems/remove-all-adjacent-duplicates-in-string-ii/
// @Title  : 删除字符串中的所有相邻重复项 II
// @Auther : sun_ds
// @Date   : 2019/10/17

/*  题目描述：
    给你一个字符串 s，「k 倍重复项删除操作」将会从 s 中选择 k 个相邻且相等的字母，并删除它们，使被删去的字符串的左侧和右侧连在一起。

    你需要对 s 重复进行无限次这样的删除操作，直到无法继续为止。

    在执行完所有删除操作后，返回最终得到的字符串。

    本题答案保证唯一。

     

    示例 1：

    输入：s = "abcd", k = 2
    输出："abcd"
    解释：没有要删除的内容。
    示例 2：

    输入：s = "deeedbbcccbdaa", k = 3
    输出："aa"
    解释：
    先删除 "eee" 和 "ccc"，得到 "ddbbbdaa"
    再删除 "bbb"，得到 "dddaa"
    最后删除 "ddd"，得到 "aa"
    示例 3：

    输入：s = "pbbcggttciiippooaais", k = 2
    输出："ps"
     

    提示：

    1 <= s.length <= 10^5
    2 <= k <= 10^4
    s 中只含有小写英文字母。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/remove-all-adjacent-duplicates-in-string-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
 * 删除字符串中的所有相邻重复项
 *
 * 开辟一个数组保存当前字符连续的次数
 * 达到k个连续就rease掉字符串中的字符，并且位置倒回i-k。
 * 最终得到结果
 *
 * 注意：i-k时容易出现小于0的情况。
 *
 */


#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string removeDuplicates(string s, int k) {
        if(k==0) return s;
        int n=s.length();
        if(n<k) return s;
        int cnt[n];
        memset(cnt,0,sizeof(cnt));
        cnt[0] = 1;
        for(int i=1;i<s.length();i++){
            if(i>0&&s[i-1]==s[i]) {
                cnt[i] = cnt[i - 1] + 1;
                if(cnt[i]==k){
                    s.erase(i-k+1,k);
                    i -= k;
                }
            }
            else cnt[i] = 1;
        }
        return s;
    }
};

int main()
{
    string s("nnwssswwnvbnnnbbqhhbbbhmmmlllm");
    int k = 3;
    Solution su;
    auto res = su.removeDuplicates(s,k);
    cout << res << endl;
    return 0;
}