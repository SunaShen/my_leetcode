// @File   : 54_kthLargest.cpp
// @Source : https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-di-kda-jie-dian-lcof/
// @Title  : 面试题54. 二叉搜索树的第k大节点
// @Auther : sun_ds
// @Date   : 2020/4/1

/**  题目描述：
    给定一棵二叉搜索树，请找出其中第k大的节点。

     

    示例 1:

    输入: root = [3,1,4,null,2], k = 1
       3
      / \
     1   4
      \
       2
    输出: 4
    示例 2:

    输入: root = [5,3,6,2,4,null,null,1], k = 3
           5
          / \
         3   6
        / \
       2   4
      /
     1
    输出: 4
     

    限制：

    1 ≤ k ≤ 二叉搜索树元素个数

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-di-kda-jie-dian-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 逆中序遍历
 *
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int res = 0;
    bool func(TreeNode* root,int &k){
        if(root==NULL) return false;
        if(func(root->right,k)) return true;
        if(k==1){
            res = root->val;
            return true;
        }
        k--;
        if(func(root->left,k)) return true;
        return false;
    }
    int kthLargest(TreeNode* root, int k) {
        func(root,k);
        return res;
    }
};


