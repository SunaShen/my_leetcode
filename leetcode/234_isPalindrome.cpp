// @File   : 234_isPalindrome.cpp
// @Source : https://leetcode-cn.com/problems/palindrome-linked-list/
// @Title  : 234. 回文链表
// @Auther : sun_ds
// @Date   : 2020/10/23

/**  题目描述：
    请判断一个链表是否为回文链表。

    示例 1:

    输入: 1->2
    输出: false
    示例 2:

    输入: 1->2->2->1
    输出: true
    进阶：
    你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/palindrome-linked-list
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 快慢指针找到链表中点，将链表分割成两部分。
 * 后半部分逆序。
 * 比较前后两部分
 *
 * 时间复杂度 O(N)
 * 空间复杂度 O(1)
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
    bool isPalindrome(ListNode* head) {
        if(head == nullptr) return true;
        // 找到中点
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }
        // 反转后半部分
        ListNode* cur =  slow->next;
        ListNode* pre = nullptr;
        while(cur != nullptr){
            ListNode* temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        // 比较前后部分
        ListNode* p1 = head;
        ListNode* p2 = pre;
        while(p1 != nullptr && p2 != nullptr){
            if(p1->val != p2->val){
                return false;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        return true;
    }
};
