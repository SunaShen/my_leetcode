// @File   : 143_reorderList.cpp
// @Source : https://leetcode-cn.com/problems/reorder-list/
// @Title  : 143. 重排链表
// @Auther : sun_ds
// @Date   : 2020/7/5

/**  题目描述：
    给定一个单链表 L：L0→L1→…→Ln-1→Ln ，
    将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…

    你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

    示例 1:

    给定链表 1->2->3->4, 重新排列为 1->4->2->3.
    示例 2:

    给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/reorder-list
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 1.不使用额外空间
 *  快慢指针找到中点。
 *  后半部分反转。
 *  前后部分拼接。
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
class Solution {
public:
    void reorderList(ListNode* head) {
        if(head == nullptr || head->next == nullptr) return;
        ListNode* l = head;
        ListNode* r = head->next;
        while(r != nullptr && r->next != nullptr){
            r = r->next->next;
            l = l->next;
        }
        r = l->next;
        l->next = nullptr;
        while(r != nullptr){
            ListNode* temp = r->next;
            r->next = l->next;
            l->next = r;
            r = temp;
        }
        r = l->next;
        l->next = nullptr;
        l = head;
        while(r != nullptr){
            ListNode* temp = r->next;
            r->next = l->next;
            l->next = r;
            l = r->next;
            r = temp;
        }
    }
};

