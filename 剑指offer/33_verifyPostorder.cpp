// @File   : 33_verifyPostorder.cpp
// @Source : https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/
// @Title  : 面试题33. 二叉搜索树的后序遍历序列
// @Auther : sun_ds
// @Date   : 2020/4/2

/**  题目描述：
    输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。

     

    参考以下这颗二叉搜索树：

         5
        / \
       2   6
      / \
     1   3
    示例 1：

    输入: [1,6,3,2,5]
    输出: false
    示例 2：

    输入: [1,3,2,6,5]
    输出: true
     

    提示：

    数组长度 <= 1000

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.递归
 * 二叉树的后序遍历 左子树-右子树-根
 * 二叉搜索树特性， 左子树 < 根 < 右子树
 * 从前往后遍历，比较每个值与根(最后一个值)之间的大小关系，找到左右子树的切分点。
 * 即找到第一个值大于根的位置。则该位置之前为左子树部分。该点与根之间的位置为右子树。
 * 判断是否合法，由上述过程可知左子树已经合法，需要遍历切分点与根之间的值是否都大于根，如果不满足返回false。
 * 如果都满足。则进行递归左子树和右子树。func(postorder,l,mid-1) func(postorder,mid,r-1)
 * 注意左子树范围 [l,mid-1] 右子树范围 [mid,r-1] 根为 r
 *
 * 递归结束条件，l>=r 此时最多只有一个节点，一定满足。
 *
 * 2.反转+单调栈
 * 后序遍历 左子树-右子树-根
 * 反向后序遍历 根 - 右子树 - 左子树
 * 二叉搜索树性质  根 - 递增序列 - 间断(转向左子树了) - 递增序列
 * 维护单调递增栈。当postorder[i]小于栈顶时，可知当前元素转向左子树了。需要将元素依次出栈找到稍大于当前值的元素即为左子树的根。
 * 后续遍历的值都默认是这个根的左子树成员，所以都应该小于该根pre_max，否则，不满足二叉搜索树特性，返回false。
 *
 */

//递归
class Solution {
public:
    bool func(vector<int>& postorder,int l,int r){
        if(l>=r) return true;
        int mid=l;
        while(postorder[mid] < postorder[r]) mid++;
        int index = mid;
        while(postorder[index] > postorder[r]) index++;
        //右子树是否合法与递归左子树右子树合并了
        return index==r&&func(postorder,l,mid-1)&&func(postorder,mid,r-1);
    }
    bool verifyPostorder(vector<int>& postorder) {
        return func(postorder,0,postorder.size()-1);
    }
};

//逆序+单调栈
class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        int n = postorder.size();
        stack<int> s;
        int pre_max = INT_MAX;
        //逆序遍历
        for(int i=n-1;i>=0;i--){
            if(postorder[i] > pre_max){
                //左子树不能大于根
                return false;
            }
            //转向左子树了 出栈找到左子树的根(大于左子树且最接近的值)，更新pre_max
            while(!s.empty()&&s.top()>postorder[i]){
                pre_max = s.top();
                s.pop();
            }
            s.push(postorder[i]);
        }
        return true;
    }
};


