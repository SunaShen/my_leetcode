// @File   : 275_hIndex.cpp
// @Source : https://leetcode-cn.com/problems/h-index-ii/
// @Title  : H指数 II
// @Auther : sun_ds
// @Date   : 2020/1/17

/**  题目描述：
    给定一位研究者论文被引用次数的数组（被引用次数是非负整数），数组已经按照升序排列。编写一个方法，计算出研究者的 h 指数。

    h 指数的定义: “h 代表“高引用次数”（high citations），一名科研人员的 h 指数是指他（她）的 （N 篇论文中）至多有 h 篇论文分别被引用了至少 h 次。（其余的 N - h 篇论文每篇被引用次数不多于 h 次。）"

     

    示例:

    输入: citations = [0,1,3,5,6]
    输出: 3
    解释: 给定数组表示研究者总共有 5 篇论文，每篇论文相应的被引用了 0, 1, 3, 5, 6 次。
         由于研究者有 3 篇论文每篇至少被引用了 3 次，其余两篇论文每篇被引用不多于 3 次，所以她的 h 指数是 3。
     

    说明:

    如果 h 有多有种可能的值 ，h 指数是其中最大的那个。

     

    进阶：

    这是 H指数 的延伸题目，本题中的 citations 数组是保证有序的。
    你可以优化你的算法到对数时间复杂度吗？

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/h-index-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 * H指数:有h篇论文其中每篇论文被引用至少h次。h为最大值。
 * 且输入时按照引用数升序排列的。
 *
 * 1.直方图法
 *  遍历寻找citations[citations.size() - 1 - i] <= i 的i即为h指数。
 *
 * 2.二分法
 *  首先citations是升序排列的。
 *  citations[i]为第i本书被引用的次数。由于升序排列所以，总的引用大于i的书的个数为 (len - 1) - i + 1 = len - i个。
 *  需要找到满足citations[i] >= len - i中的len - i的最大值。
 *
 *  使用二分法。
 *  若citations[mid] < len - mid则满足条件的在右边。l = mid+1;
 *  若citations[mid] >= len - mid则满足条件的在左边(包含当前mid)。r = mid;(包含当前mid，所以不能mid - 1);
 *
 *  最终l==r跳出循环，则len-l就是最终的h指数。
 *
 *
 */


class Solution {
public:
    int hIndex(vector<int>& citations) {
        int i=0;
        while(i < citations.size() && citations[citations.size() - 1 - i] > i) ++i;
        return i;
    }
};


class Solution {
public:
    int hIndex(vector<int>& citations) {
        int len = citations.size();
        //判断(若另r = len则不用判断了。)
        if (len == 0 || citations[len - 1] == 0) {
            return 0;
        }
        int l = 0, r = len-1;
        while(l<r){
            int mid = l + ((r-l) >>1);
            if(citations[mid] < len - mid){
                l = mid + 1;
            }else{
                r = mid;
            }
        }
        return len - l;
    }
};


class Solution {
public:
    int hIndex(vector<int>& citations) {
        int len = citations.size();
        int l = 0, r = len;
        while(l<r){
            int mid = l + ((r-l) >>1);
            if(citations[mid] < len - mid){
                l = mid + 1;
            }else{
                r = mid;
            }
        }
        return len - l;
    }
};
