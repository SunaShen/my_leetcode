// @File   : 36_treeToDoublyList.cpp
// @Source : https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof/
// @Title  : 面试题36. 二叉搜索树与双向链表
// @Auther : sun_ds
// @Date   : 2020/4/2

/**  题目描述：
    输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。

     

    为了让您更好地理解问题，以下面的二叉搜索树为例：

     



     

    我们希望将这个二叉搜索树转化为双向循环链表。链表中的每个节点都有一个前驱和后继指针。对于双向循环链表，第一个节点的前驱是最后一个节点，最后一个节点的后继是第一个节点。

    下图展示了上面的二叉搜索树转化成的链表。“head” 表示指向链表中有最小元素的节点。

     



     

    特别地，我们希望可以就地完成转换操作。当转化完成以后，树中节点的左指针需要指向前驱，树中节点的右指针需要指向后继。还需要返回链表中的第一个节点的指针。

     

    注意：本题与主站 426 题相同：https://leetcode-cn.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/

    注意：此题对比原题有改动。



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 *
 * 1.中序遍历
 *  记录前面节点pre。
 *  将当前节点的left指向pre pre的right指向当前
 *  并更新pre为当前节点
 *
 *  第一个节点为head。最左边。即最小值。
 *
 *
 * 递归版
 * 迭代版
 *
 *
 */

//迭代版
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
private:
//    Node* head = nullptr,pre = nullptr; 出大问题
    Node* head = nullptr,* pre = nullptr;
public:
    void func(Node* root){
        if(!root) return;
        func(root->left);
        if(!head){
            head = root;
            pre = root;
        }else{
            pre->right = root;
            root->left = pre;
            pre = root;
        }
        func(root->right);
    }
    Node* treeToDoublyList(Node* root) {
        if(root==nullptr) return nullptr;
        func(root);
        head->left = pre;
        pre->right = head;
        return head;
    }
};

//递归版
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if(root==nullptr) return nullptr;
        Node* head = nullptr,* pre = nullptr;
        stack<Node*> s;
        Node* temp = root;
        while(!s.empty()||temp!=nullptr){
            while(temp!=nullptr){
                s.push(temp);
                temp = temp->left;
            }
            temp = s.top();
            s.pop();
            if(head==nullptr){
                head = temp;
                pre = temp;
            }else{
                pre->right = temp;
                temp->left = pre;
                pre = temp;
            }
            temp = temp->right;
        }
        head->left = pre;
        pre->right = head;
        return head;
    }
};