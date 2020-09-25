// @File   : 114_flatten.cpp
// @Source : https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/
// @Title  : 114. 二叉树展开为链表
// @Auther : sun_ds
// @Date   : 2020/8/2

/**  题目描述：
    给定一个二叉树，原地将它展开为一个单链表。

     

    例如，给定二叉树

        1
       / \
      2   5
     / \   \
    3   4   6
    将其展开为：

    1
     \
      2
       \
        3
         \
          4
           \
            5
             \
              6

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.前序遍历
 * 按照前序遍历顺序将节点存入 vector 中。然后遍历数组，组合各个节点。将当前节点左孩子置为空，右孩子置为下一个节点。
 * 时间复杂度 O(N)
 * 空间复杂度 O(N)
 *
 * 2.前序遍历
 * 边遍历边构造链表，使用 stack 暂时存储节点信息。 只适合迭代法，可以存储左右孩子。
 * pre 为遍历的前一个节点。
 * 时间复杂度 O(N)
 * 空间复杂度 O(N)
 *
 * 3.前序节点
 * https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list/solution/er-cha-shu-zhan-kai-wei-lian-biao-by-leetcode-solu/
 * 每次找到当前节点的前序节点 pre，然后将 cur 的右子树放到 pre 的右孩子位置，并将 cur 的左子树放到右子树位置。
 * 然后 cur = cur->right.
 * 若 cur 没有左子树则直接 cur = cur->right.
 * 时间复杂度 O(N)
 * 空间复杂度 O(1)
 *
 */


// 前序遍历
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
    void flatten(TreeNode* root) {
        vector<TreeNode*> v;
        stack<TreeNode*> s;
        if (root == nullptr) return;
        TreeNode* temp = root;
        while (!s.empty() || temp != nullptr) {
            while (temp != nullptr) {
                v.push_back(temp);
                s.push(temp);
                temp = temp->left;
            }
            temp = s.top();s.pop();
            temp = temp->right;
        }
        for (int i = 1; i < v.size(); ++i) {
            v[i-1]->left = nullptr;
            v[i-1]->right = v[i];
        }
    }
};

// 前序遍历 迭代 stack
class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        auto stk = stack<TreeNode*>();
        stk.push(root);
        TreeNode *prev = nullptr;
        while (!stk.empty()) {
            TreeNode *curr = stk.top(); stk.pop();
            if (prev != nullptr) {
                prev->left = nullptr;
                prev->right = curr;
            }
            TreeNode *left = curr->left, *right = curr->right;
            if (right != nullptr) {
                stk.push(right);
            }
            if (left != nullptr) {
                stk.push(left);
            }
            prev = curr;
        }
    }
};


// 前序节点
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
    void flatten(TreeNode* root) {
        TreeNode* cur = root;
        TreeNode* next;
        TreeNode* pre;
        while (cur != nullptr) {
            if (cur->left != nullptr) {
                next = cur->left;
                pre = next;
                while (pre->right != nullptr) {
                    pre = pre->right;
                }
                pre->right = cur->right;
                cur->right = next;
                cur->left = nullptr;
            }
            cur = cur->right;
        }
    }
};
