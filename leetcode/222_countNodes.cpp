// @File   : 222_countNodes.cpp
// @Source : https://leetcode-cn.com/problems/count-complete-tree-nodes/
// @Title  : 222. 完全二叉树的节点个数
// @Auther : sun_ds
// @Date   : 2020/8/23

/**  题目描述：
    给出一个完全二叉树，求出该树的节点个数。

    说明：

    完全二叉树的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层，则该层包含 1~ 2h 个节点。

    示例:

    输入:
        1
       / \
      2   3
     / \  /
    4  5 6

    输出: 6

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/count-complete-tree-nodes
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 遍所有节点
 *  递归，遍历所有节点。
 *  时间复杂度 O(N)
 *  空间复杂度 O(log(N))
 *
 * 2. 二分法(左右子树树高度)
 * 根据完全二叉树性质，除最后一层不满之外，上面层都是满的。且不满也只能是右边缺节点，左边是满的。
 *
 * 由于是完全二叉树，所以子树的深度即为最左端节点的深度。
 * 分别获取左右子树的深度。
 *
 * 若左右子树深度depth相同，说明最后一层的节点覆盖超过半数啦。
 * 所以左子树为满二叉树，节点个数为 2^depth - 1. 在加上根节点，已确定的节点个数为 2^depth - 1 + 1 = 1 << depth;
 * 然后在右子树中递归统计节点个数。
 * 结束条件，root == nullptr。
 *
 * 若左右子树深度depth不相同，那么一定是 depth_left = depth_right + 1， 说明最后一层的节点覆盖没有超过半数。
 * 此时，右子树为满二叉树。 右子树节点数为 2^depth_right - 1, 再加上根节点，已确定的个数为 2^depth_right - 1 + 1 = 1 << depth_right
 * 然后在左子树中递归统计节点个数。
 * 结束条件，root == nullptr。
 *
 * 时间复杂度 O((logN)^2) 递归和求深度
 * 空间复杂度 O(1)
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
    int countNodes(TreeNode* root) {
        return root == nullptr ? 0 : 1 + countNodes(root->left) + countNodes(root->right);
    }
};

// 二分法
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
    int getDepth(TreeNode* root) {
        int d = 0;
        while(root != nullptr) {
            d++;
            root = root->left;
        }
        return d;
    }
    int countNodes(TreeNode* root) {
        if (root == nullptr) return 0;
        int count = 0;
        int left = getDepth(root->left);
        int right = getDepth(root->right);

        if (left == right) {  //最后一个叶子节点在右边
            count += (1 << left);
            count += countNodes(root->right);
        } else {    //最后一个叶子节点在左边    left > right
            count += (1 << right);
            count += countNodes(root->left);
        }
        return count;
    }
};