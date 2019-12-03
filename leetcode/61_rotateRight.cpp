// @File   : 61_rotateRight.cpp
// @Source : https://leetcode-cn.com/problems/rotate-list/
// @Title  : 旋转链表
// @Auther : sun_ds
// @Date   : 2019/11/15

/*  题目描述：
    给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。

    示例 1:

    输入: 1->2->3->4->5->NULL, k = 2
    输出: 4->5->1->2->3->NULL
    解释:
    向右旋转 1 步: 5->1->2->3->4->NULL
    向右旋转 2 步: 4->5->1->2->3->NULL
    示例 2:

    输入: 0->1->2->NULL, k = 4
    输出: 2->0->1->NULL
    解释:
    向右旋转 1 步: 2->0->1->NULL
    向右旋转 2 步: 1->2->0->NULL
    向右旋转 3 步: 0->1->2->NULL
    向右旋转 4 步: 2->0->1->NULL

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/rotate-list
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
 * 链表循环右移
 * 注意移位数k可以大于链表长度
 *
 * 1.一次遍历到链表尾部并将链表首位相接(循环链表)，得到链表长度。
 *   移位数对链表长度n取余，k%n。从head开始，即第n-k%n位位新的链表尾，n-k%n+1位新的链表头
 *
 * 2.借鉴查找链表中倒数第k个元素的方法，使用双指针，其中一个指针断开为头，另一个指针指向链表尾接到链表头
 *   该方法在k<n时可以，当k>n时，处理复杂。。。
 *
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
    ListNode* rotateRight(ListNode* head, int k) {
        if(head==NULL||head->next==NULL) return head;

        int c=1;
        ListNode *p = head;
        while(p->next){
            ++c;
            p = p->next;
        }
        p->next = head;
        p = head;
        for(int i=1;i<(c-k%c);i++)
        {
            p = p->next;
        }
        head = p->next;
        p->next = NULL;
        return head;
    }
};

