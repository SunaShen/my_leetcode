// @File   : 16.18_patternMatching.cpp
// @Source : https://leetcode-cn.com/problems/pattern-matching-lcci/
// @Title  : 面试题 16.18. 模式匹配
// @Auther : sun_ds
// @Date   : 2020/6/22

/**  题目描述：
    你有两个字符串，即pattern和value。 pattern字符串由字母"a"和"b"组成，用于描述字符串中的模式。例如，字符串"catcatgocatgo"匹配模式"aabab"（其中"cat"是"a"，"go"是"b"），该字符串也匹配像"a"、"ab"和"b"这样的模式。但需注意"a"和"b"不能同时表示相同的字符串。编写一个方法判断value字符串是否匹配pattern字符串。

    示例 1：

    输入： pattern = "abba", value = "dogcatcatdog"
    输出： true
    示例 2：

    输入： pattern = "abba", value = "dogcatcatfish"
    输出： false
    示例 3：

    输入： pattern = "aaaa", value = "dogcatcatdog"
    输出： false
    示例 4：

    输入： pattern = "abba", value = "dogdogdogdog"
    输出： true
    解释： "a"="dogdog",b=""，反之也符合规则
    提示：

    0 <= len(pattern) <= 1000
    0 <= len(value) <= 1000
    你可以假设pattern只包含字母"a"和"b"，value仅包含小写字母。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/pattern-matching-lcci
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 首先确定 a,b 对应字符串的长度。
 * 通过这些长度就可以划分子串进行比较了。
 * 设，pattern中出现了 ca 个 a 和 cb 个 b。 其中 ca + cb = pattern.size();
 * a,b 对应的字符串的长度为 la 和 lb。
 * 则有，ca * la + cb * lb = value.size(); 即 ca * la + (pattern.size() - ca) * lb = value.size()
 * 该方程中 ca 为已知量，而 la 和 lb 为未知量。为 二元一次方程。其中 la 和 lb 为自然数。
 * 枚举各个 la，lb，找到合适的解。
 *
 * 注意边界
 *
 *
 */

class Solution {
public:
    bool patternMatching(string pattern, string value) {
        int plen = pattern.size(), vlen = value.size();
        if (plen == 0 && vlen == 0) return true;  //全为空，成立
        if (plen == 0) return false; //pattern 为空，value 为空，不成立

        int ac = 0, bc = 0;
        for (int i = 0; i < plen; ++i) {
            if (pattern[i] == 'a') ac++;
            else bc++;
        }

        int la = 0, lb = 0;
        // la，lb 的取值范围
        if (ac != 0) la = vlen / ac;
        if (bc != 0) lb = vlen / bc;

        for (int i = 0; i <= la; ++i) {
            for (int j = 0; j <= lb; ++j) {
                if (i * ac + j * bc == vlen) {
                    string sa = "#"; // 标志作用
                    string sb = "#";
                    int index = 0;
                    for (int k = 0; k < plen; ++k) {
                        if (pattern[k] == 'a') {
                            if (sa == "#") sa = value.substr(index, i);
                            else {
                                if (sa != value.substr(index, i)) break;
                            }
                            index += i;
                        }
                        else {
                            if (sb == "#") sb = value.substr(index, j);
                            else {
                                if (sb != value.substr(index, j)) break;
                            }
                            index += j;
                        }
                    }
                    if (index == vlen && sa != sb) return true;
                }
            }
        }

        return false;
    }
};

