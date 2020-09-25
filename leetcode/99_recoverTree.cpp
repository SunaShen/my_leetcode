// @File   : 99_recoverTree.cpp
// @Source : https://leetcode-cn.com/problems/recover-binary-search-tree/
// @Title  : 99. 恢复二叉搜索树
// @Auther : sun_ds
// @Date   : 2020/8/8

/**  题目描述：
    二叉搜索树中的两个节点被错误地交换。

    请在不改变其结构的情况下，恢复这棵树。

    示例 1:

    输入: [1,3,null,null,2]

       1
      /
     3
      \
       2

    输出: [3,1,null,null,2]

       3
      /
     1
      \
       2
    示例 2:

    输入: [3,1,4,null,null,2]

      3
     / \
    1   4
       /
      2

    输出: [2,1,4,null,null,3]

      2
     / \
    1   4
       /
      3
    进阶:

    使用 O(n) 空间复杂度的解法很容易实现。
    你能想出一个只使用常数空间的解决方案吗？

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/recover-binary-search-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 中序遍历
 * 二叉搜索树中序遍历薛烈递增。
 *
 * 元素被交换，有两种情况。
 *  1.1 相邻元素被交换。     一组逆序对
 *       如果一个序列交换两个相邻的值必然得到一个相邻逆序对，如 1 2 3 4，交换 2 和 3 得到 1 3 2 4
 *       相邻逆序对是 3 2，那么 x 就是第一个逆序对中的 3，y 是第二个逆序对中的 2。
 *  1.2 不想理你元素被交换。  两组逆序对
 *      如果一个序列交换两个不相邻的值必然得到两个相邻逆序对，如 1 2 3 4，交换 1 和 4 得到 4 2 3 1
 *      两个相邻逆序对是 4 2 和 3 1，那么 x 就是第一个逆序对中的 4，y 是第二个逆序对中的 1。
 *
 * 中序遍历过程中，记录逆序对位置。
 * 最后，交换对应位置的值，即还原了二叉搜索树
 *
 * 时间复杂度 O(N)
 * 空间复杂度 O(H)  树高
 *
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode* temp = root;
        TreeNode* res1 = nullptr;
        TreeNode* res2 = nullptr;
        TreeNode* pre = nullptr;
        stack<TreeNode*> s;
        while (!s.empty() || temp != nullptr) {
            while(temp != nullptr) {
                s.push(temp);
                temp = temp->left;
            }
            temp = s.top();
            s.pop();
            // 记录逆序对位置
            if (pre != nullptr && temp->val < pre->val) {
                res2 = temp;
                if (res1 == nullptr) {
                    res1 = pre;
                } else {
                    break;
                }
            }
            pre = temp;
            temp = temp->right;
        }
        swap(res1->val, res2->val);
    }
};
