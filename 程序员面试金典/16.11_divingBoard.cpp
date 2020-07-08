// @File   : 16.11_divingBoard.cpp
// @Source : https://leetcode-cn.com/problems/diving-board-lcci/
// @Title  : 面试题 16.11. 跳水板
// @Auther : sun_ds
// @Date   : 2020/7/8

/**  题目描述：
    你正在使用一堆木板建造跳水板。有两种类型的木板，其中长度较短的木板长度为shorter，长度较长的木板长度为longer。你必须正好使用k块木板。编写一个方法，生成跳水板所有可能的长度。

    返回的长度需要从小到大排列。

    示例：

    输入：
    shorter = 1
    longer = 2
    k = 3
    输出： {3,4,5,6}
    提示：

    0 < shorter <= longer
    0 <= k <= 100000


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/diving-board-lcci
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 长短木板总数为 k。则组合一共是 k+1 种情况。
 * 当 k==0 时，返回空数组。
 * 否则，返回 k+1 中情况递增的序列。
 *
 * 每个组合的总长度 Li = shorter*i + longer*(k-i);
 * 假设另有一个 j!=i 。 Lj = shorter*j + longer*(k-j);
 * 使得 Li == Lj
 * Li - Lj = (i-j)shorter + longer*(j-i) = (i-j)*(shorter-longer);
 * 且 i!=j shorter!=longer 时 Li 与 Lj 一定不相等。且 L 随着 longer 的个数增加而增加。
 * 而当shorter==longer时，其实一共就只有一种组合。即 k*shorter
 *
 *
 */

// set 去重
class Solution {
public:
    vector<int> divingBoard(int shorter, int longer, int k) {
        set<int> res;
        if(k==0) return {};
        for(int i=0;i<=k;i++){
            res.insert(shorter*(k-i) + longer*i);
        }
        return vector<int> (res.begin(), res.end());
    }
};


class Solution {
public:
    vector<int> divingBoard(int shorter, int longer, int k) {
        if (k == 0) {
            return vector <int> ();
        }

        if (shorter == longer) {
            return vector <int> (1, shorter * k);
        }

        vector <int> lengths(k + 1);
        for (int i = 0; i <= k; ++i) {
            lengths[i] = shorter * (k - i) + longer * i;
        }

        return lengths;
    }
};


