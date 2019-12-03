// @File   : 11_maxArea.cpp
// @Source : https://leetcode-cn.com/problems/container-with-most-water/
// @Title  : 盛最多水的容器
// @Auther : sun_ds
// @Date   : 2019/10/31

/*  题目描述：
    给定 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

    说明：你不能倾斜容器，且 n 的值至少为 2。



    图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。

     

    示例:

    输入: [1,8,6,2,5,4,8,3,7]
    输出: 49

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/container-with-most-water
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 * 盛最多水的容器
 * 容器盛水量即面积，由两个边长来决定。
 * 一条边为左右两个高度中低的那一个(木桶效应)，另一条边由左右之间的位置距离
 *
 * 1.暴力解
 *   固定左边边，遍历所有 0--n-2
 *   遍历右边边，i+1 -- n-1
 *   计算面积 (j-i)*min(h[i],h[j])
 *   保存最大面积
 *
 *   共有n(n-1)/2种组合，复杂度O(n^2)
 *
 * 2.双指针
 *   左右两个指针分别指向左右两个边。逐渐向中间靠拢。保持i<j，并记录下最大面积。
 *   起始时左右指针分别指向头和尾
 *   靠拢规则：短边收缩
 *   当前两边距离比较大，收缩完之后距离肯定变小，为了求得最大面积，故木桶的最短边应该有些抬升。
 *   因此，短边向内收缩，这样还有机会面积变大。如若收缩长边，则面积减小或不变。
 *
 *   遍历一次即得到结果。复杂度O(n)
 *
 *   其实无论是移动短指针和长指针都是一种可行求解。
 *   只是，一开始就已经把指针定义在两端，如果短指针不动，而把长指针向着另一端移动，两者的距离已经变小了，无论会不会遇到更高的指针，结果都只是以短的指针来进行计算。
 *   故移动长指针是无意义的。
 *
 * 双指针法正确性证明：
 * https://leetcode-cn.com/problems/container-with-most-water/solution/shuang-zhi-zhen-fa-zheng-que-xing-zheng-ming-by-r3/
 *
 *
 *
 */

//暴力解 O(n^2) 1996ms
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        if(n < 2) return 0;
        int max = INT_MIN;
        for(int i=0;i<n-1;++i){
            for(int j=i+1;j<n;++j){
                int v = (j - i)*min(height[i],height[j]);
                max = v > max ? v : max;
            }
        }
        return max;
    }
};

//双指针 O(n) 20ms
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        if(n < 2) return 0;
        int max = INT_MIN;
        int i=0,j=n-1;
        while(i<j){
            int v = (j - i)*min(height[i],height[j]);
            max = v > max ? v : max;
            height[i] < height[j] ? ++i : --j;
        }
        return max;
    }
};

