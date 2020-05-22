// @File   : 958_isCompleteTree.cpp
// @Source : https://leetcode-cn.com/problems/check-completeness-of-a-binary-tree/
// @Title  : 958. 二叉树的完全性检验
// @Auther : sun_ds
// @Date   : 2020/5/22

/**  题目描述：
    给定一个二叉树，确定它是否是一个完全二叉树。

    百度百科中对完全二叉树的定义如下：

    若设二叉树的深度为 h，除第 h 层外，其它各层 (1～h-1) 的结点数都达到最大个数，第 h 层所有的结点都连续集中在最左边，这就是完全二叉树。（注：第 h 层可能包含 1~ 2h 个节点。）

     

    示例 1：



    输入：[1,2,3,4,5,6]
    输出：true
    解释：最后一层前的每一层都是满的（即，结点值为 {1} 和 {2,3} 的两层），且最后一层中的所有结点（{4,5,6}）都尽可能地向左。
    示例 2：



    输入：[1,2,3,4,5,null,7]
    输出：false
    解释：值为 7 的结点没有尽可能靠向左侧。
     

    提示：

    树中将会有 1 到 100 个结点。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/check-completeness-of-a-binary-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 使用队列执行层序遍历的顺序。
 * 当出现第一个 nullptr 之后，后面只能全部是 nullptr。
 * 否则，不是完全二叉树。
 *
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
    bool isCompleteTree(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        bool flag = false;
        while(!q.empty()){
            TreeNode* temp = q.front();
            q.pop();
            if(temp!=nullptr){
                if(flag) return false;
                q.push(temp->left);
                q.push(temp->right);
            }else{
                flag = true;
            }
        }
        return true;
    }
};

