// @File   : 24_swapPairs.cpp
// @Source : https://leetcode-cn.com/problems/swap-nodes-in-pairs/
// @Title  : 两两交换链表中的节点
// @Auther : sun_ds
// @Date   : 2019/11/14

/*  题目描述：
    给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。

    你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。

     

    示例:

    给定 1->2->3->4, 你应该返回 2->1->4->3.

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/swap-nodes-in-pairs
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 * 两两交换链表中的节点
 *
 * 各显神通吧
 *
 */

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
    ListNode* swapPairs(ListNode* head) {
        if(head==NULL||head->next==NULL) return head;
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* p1 = dummy;
        ListNode* p2 = head->next;
        while(1){

            p1->next->next = p2->next;
            p2->next = p1->next;
            p1->next = p2;
            p2 = p2->next;

            if(p2->next==NULL||p2->next->next==NULL) break;
            p2 = p2->next->next;
            p1 = p1->next->next;
        }
        return dummy->next;
    }
};


//速度快，使用中间变量
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        ListNode *c = dummy;
        while(c->next&&c->next->next){
            ListNode *a = c->next;
            ListNode *b = c->next->next;
            c->next = b;
            a->next = b->next;
            b->next = a;
            c = c->next->next;
        }
        return dummy->next;
    }
};




//递归，容易理解
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        auto p1 = head;
        auto p2 = p1->next;
        p1->next = swapPairs(p2->next);
        p2->next = p1;
        return p2;
    }
};
