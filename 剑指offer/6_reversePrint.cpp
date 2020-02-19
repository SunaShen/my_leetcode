// @File   : 6_reversePrint.cpp
// @Source : https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof/
// @Title  : 面试题06. 从尾到头打印链表
// @Auther : sun_ds
// @Date   : 2020/2/19

/**  题目描述：
    输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。

     

    示例 1：

    输入：head = [1,3,2]
    输出：[2,3,1]
     

    限制：

    0 <= 链表长度 <= 10000

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 倒序输出链表
 *
 * 1.辅助栈法
 * 辅助栈，将链表中的值从前往后依次入栈，然后依次出栈存在数组中。
 * 时间复杂度O(N)
 * 空间复杂度O(N)
 *
 * 2.递归
 * 利用递归特性，在返回时将各数值存入vector中。
 * 即反序存入。
 *
 *
 */

//辅助栈
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        stack<int> s;
        ListNode* temp = head;
        while(temp!=NULL){
            s.push(temp->val);
            temp = temp->next;
        }
        vector<int> ans;
        while(!s.empty()){
            ans.push_back(s.top());
            s.pop();
        }
        return ans;
    }
};

//递归
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> ans;
    void func(ListNode* root){
        if(root == NULL) return;
        func(root->next);
        ans.push_back(root->val);
    }
    vector<int> reversePrint(ListNode* head) {
        func(head);
        return ans;
    }
};
