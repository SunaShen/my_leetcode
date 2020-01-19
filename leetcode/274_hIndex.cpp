// @File   : 274_hIndex.cpp
// @Source : https://leetcode-cn.com/problems/h-index/
// @Title  : H指数
// @Auther : sun_ds
// @Date   : 2020/1/17

/**  题目描述：
    给定一位研究者论文被引用次数的数组（被引用次数是非负整数）。编写一个方法，计算出研究者的 h 指数。

    h 指数的定义: “h 代表“高引用次数”（high citations），一名科研人员的 h 指数是指他（她）的 （N 篇论文中）至多有 h 篇论文分别被引用了至少 h 次。（其余的 N - h 篇论文每篇被引用次数不多于 h 次。）”

     

    示例:

    输入: citations = [3,0,6,1,5]
    输出: 3
    解释: 给定数组表示研究者总共有 5 篇论文，每篇论文相应的被引用了 3, 0, 6, 1, 5 次。
         由于研究者有 3 篇论文每篇至少被引用了 3 次，其余两篇论文每篇被引用不多于 3 次，所以她的 h 指数是 3。
     

    说明: 如果 h 有多种可能的值，h 指数是其中最大的那个。



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/h-index
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * H指数:有h篇论文其中每篇论文被引用至少h次。h为最大值。
 *
 * 1.求大于h次引用的论文数-(有与3类似的思想，但实现太蠢了)。
 *  求大于h=[1,max]次引用的论文数,存储在cum中。
 *  反向遍历cum(求最大h),找到第一个cum[i-1]>=i的i，即h指数=i。
 *
 * 2.直方图
 * 我们想象一个直方图，其中x轴表示文章，y轴表示每篇文章的引用次数。
 * 如果将这些文章按照引用次数降序排序并在直方图上进行表示，那么直方图上的最大的正方形的边长h就是我们所要求的h。
 *
 * 时间复杂度O(nlogn) 排序的复杂度
 * 空间复杂度O(1)
 *
 *
 *
 * 作者：LeetCode
 * 链接：https://leetcode-cn.com/problems/h-index/solution/hzhi-shu-by-leetcode/
 * 来源：力扣（LeetCode）
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 *
 * 3.计数排序
 *  基于比较的排序算法存在时间复杂度下界 O(nlogn)，如果要得到时间复杂度更低的算法，就必须考虑不基于比较的排序。
 *  要得到时间复杂度更低的算法. 可以考虑最常用的不基于比较的排序，计数排序。
 *  然而，论文的引用次数可能会非常多，这个数值很可能会超过论文的总数n，因此使用计数排序是非常不合算的（会超出空间限制）。
 *  在这道题中，我们可以通过一个不难发现的结论来让计数排序变得有用，即：如果一篇文章的引用次数超过论文的总数n，那么将它的引用次数降低为n 也不会改变h指数的值。
 *
 *
 *  统计各个引用次数出现的次数。找到第一个最大的出现次数大于等于引用次数的次数作为h。
 *
 *  时间复杂度O(n)
 *  空间复杂度O(n)
 *
 *
 *  作者：LeetCode
 *  链接：https://leetcode-cn.com/problems/h-index/solution/hzhi-shu-by-leetcode/
 *  来源：力扣（LeetCode）
 *  著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 *
 *
 */

class Solution {
public:
    int hIndex(vector<int>& citations) {
        int len = citations.size();
        if(len == 0) return 0;
        vector<int> cum;
        sort(citations.begin(),citations.end());
        int j=0;
        for(int i=1;i <=*max_element(citations.begin(),citations.end());++i){
            while(j<len&&citations[j] <i) ++j;
            cum.push_back(len - j);
        }
        for(int i=cum.size();i>0;--i){
            if(cum[i-1]>=i) return i;
        }
        return 0;
    }
};


class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.rbegin(),citations.rend());
        int i=0;
        while(i < citations.size() && citations[i] > i) ++i;
        return i;
    }
};

public class Solution {
public int hIndex(int[] citations) {
        int n = citations.length;
        int[] papers = new int[n + 1];
        // 计数
        for (int c: citations)
            papers[Math.min(n, c)]++;
        // 找出最大的 k
        int k = n;
        for (int s = papers[n]; k > s; s += papers[k])
            k--;
        return k;
    }
}
