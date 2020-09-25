// @File   : 109_sortedListToBST.cpp
// @Source : https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree/
// @Title  : 109. 有序链表转换二叉搜索树
// @Auther : sun_ds
// @Date   : 2020/8/18

/**  题目描述：
    给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。

    本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

    示例:

    给定的有序链表： [-10, -3, 0, 5, 9],

    一个可能的答案是：[0, -3, 9, -10, null, 5], 它可以表示下面这个高度平衡二叉搜索树：

          0
         / \
       -3   9
       /   /
     -10  5

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/convert-sorted-list-to-binary-search-tree
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.递归
 * 每次以中间为根节点，分为两部分。
 * 递归执行。
 *
 * 设置为前闭后开区间方便实现。[left，mid] ，mid，[mid->next, right]
 *
 * 时间复杂度 O(Nlog(N))
 * 空间复杂度 O(log(N))
 *
 * 2.模拟中序遍历
 * 模拟中序遍历过程，使用当前位置作为判断是否为叶子节点(需要返回)
 * 提前建一个空的根节点，因为按照链表顺序，根节点在左子树后面，所以先创建空的递归，后面到了根节点位置了再填充。
 *
 * 时间复杂度 O(N)
 * 空间复杂度 O(log(N))
 *
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
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
    ListNode* getMedian(ListNode* left, ListNode* right) {
        ListNode* fast = left;
        ListNode* slow = left;
        while (fast != right && fast->next != right) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
    TreeNode* buildTree(ListNode* left, ListNode* right) {
        if (left == right) return nullptr;
        ListNode* mid = getMedian(left, right);
        TreeNode* root = new TreeNode(mid->val);
        root->left = buildTree(left, mid);
        root->right = buildTree(mid->next, right);
        return root;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        return buildTree(head, nullptr);
    }
};

class Solution {
public:
    int getLength(ListNode* head) {
        int ret = 0;
        for (; head != nullptr; ++ret, head = head->next);
        return ret;
    }

    // head 为指针的引用 left 与 right 用来判断叶子节点
    TreeNode* buildTree(ListNode*& head, int left, int right) {
        if (left > right) {
            return nullptr;
        }
        int mid = (left + right + 1) / 2;
        // 创建根节点占位
        TreeNode* root = new TreeNode();
        root->left = buildTree(head, left, mid - 1);
        // 此时 head 是被上面 buildTree 修改过的 head，是指针的引用，类似二级指针。
        root->val = head->val;
        head = head->next;

        root->right = buildTree(head, mid + 1, right);
        return root;
    }

    TreeNode* sortedListToBST(ListNode* head) {
        int length = getLength(head);
        return buildTree(head, 0, length - 1);
    }
};

