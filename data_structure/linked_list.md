# 链表

## 基本技能

链表相关的核心点

- null/nil 异常处理
- dummy node 哑巴节点
- 快慢指针
- 插入一个节点到排序链表
- 从一个链表中移除一个节点
- 翻转链表
- 合并两个链表
- 找到链表的中间节点

## 常见题型

### [remove-duplicates-from-sorted-list](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)

> 给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。

```c++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL)
            return NULL;
        ListNode* cur = head->next;
        ListNode* last = head;
        while(cur != NULL)
        {
            if(cur->val == last->val)
            {
                cur = cur->next;
                last->next = cur;
            }
            else
            {
                cur = cur->next;
                last = last->next;
            }
        }
        return head;
    }
};
```

### [remove-duplicates-from-sorted-list-ii](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/)

> 给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中   没有重复出现的数字。

思路：链表头结点可能被删除，所以用 dummy node 辅助删除

```c++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL)
            return NULL;
        ListNode root;
        root.next = head;
        ListNode* last = &root;
        ListNode* cur = head;
        while(cur != NULL)
        {
            ListNode* tp = cur->next;
            while(tp != NULL && tp->val == cur->val)
                tp = tp->next;
            if(tp != cur->next)
                last -> next = tp;
            else
                last = last->next;
            cur = tp;
        }
        return root.next;
    }
};
```

注意点
• A->B->C 删除 B，A.next = C
• 删除用一个 Dummy Node 节点辅助（允许头节点可变）
• 访问 X.next 、X.value 一定要保证 X != nil

### [reverse-linked-list](https://leetcode-cn.com/problems/reverse-linked-list/)

> 反转一个单链表。

思路：用一个 prev 节点保存向前指针，temp 保存向后的临时指针

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == NULL)
            return NULL;
        ListNode* last = NULL;
        ListNode* cur = head;
        while(cur != NULL)
        {
            ListNode* tp = cur->next;
            cur->next = last;
            last = cur;
            cur = tp;
        }
        return last;
    }
};
```

### [reverse-linked-list-ii](https://leetcode-cn.com/problems/reverse-linked-list-ii/)

> 反转从位置  *m*  到  *n*  的链表。请使用一趟扫描完成反转。

思路：先遍历到 m 处，翻转，再拼接后续，注意指针处理

```c++
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(head->next == NULL)
            return head;
        ListNode root;
        root.next = head;
        ListNode* edge = &root;
        ListNode* cur = head;
        while(cur && (right --, --left))//left和right的值是表示index而非value
        {
            edge = cur;
            cur = cur->next;
        }
        while(cur && right --)
        {
            ListNode* tp = cur->next;
            cur->next = tp->next;
            tp->next = edge->next;
            edge->next = tp;
        }
        return root.next;
    }
};
```

### [merge-two-sorted-lists](https://leetcode-cn.com/problems/merge-two-sorted-lists/)

> 将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

思路：通过 dummy node 链表，连接各个元素

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode root;
        ListNode* cur = &root;
        while(list1 && list2)
        {
            if(list1->val < list2->val)
            {
                cur->next = list1;
                list1 = list1->next;
            }
            else
            {
                cur->next = list2;
                list2 = list2->next;
            }
            cur = cur->next;
        }
        if(list1)
            cur->next = list1;
        else
            cur->next = list2;
        return root.next;
    }
};
```

### [partition-list](https://leetcode-cn.com/problems/partition-list/)

> 给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于  *x*  的节点都在大于或等于  *x*  的节点之前。

思路：将大于 x 的节点，放到另外一个链表，最后连接这两个链表

```c++
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if(head == NULL)
            return NULL;
        ListNode large;
        ListNode less;
        ListNode* larCur = &large;
        ListNode* lesCur = &less;
        ListNode* cur = head;
        while(cur != NULL)
        {
            if(cur->val < x)
            {
                lesCur->next = cur;
                lesCur = cur;
            }
            else
            {
                larCur->next = cur;
                larCur = cur;
            }
            cur = cur->next;
        }
        lesCur->next = large.next;
        larCur->next = NULL;
        return less.next;
    }
};
```

哑巴节点使用场景

> 当头节点不确定的时候，使用哑巴节点

### [sort-list](https://leetcode-cn.com/problems/sort-list/)

> 在  *O*(*n* log *n*) 时间复杂度和常数级空间复杂度下，对链表进行排序。

思路：归并排序，找中点和合并操作

```c++
class Solution {
public:

    ListNode* sortList(ListNode* head) {
        return mergeSort(head);
    }
    ListNode* findMid(ListNode* head)
    {
        ListNode* fast = head->next;
        ListNode* slow = head;
        while(fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    ListNode* merge(ListNode* list1, ListNode* list2)
    {
        ListNode* root = new ListNode;
        ListNode* cur = root;
        while(list1 != NULL && list2 != NULL)
        {
            if(list1->val < list2 -> val)
            {
                cur->next = list1;
                list1 = list1->next;
            }
            else
            {
                cur->next = list2;
                list2 = list2->next;
            }
            cur = cur->next;
        }
        if(list1 == NULL)
            cur->next = list2;
        else
            cur->next = list1;
        return root->next;
    }

    ListNode* mergeSort(ListNode* head)
    {
        if(head == NULL || head->next == NULL)
            return head;
        ListNode* mid = findMid(head);
        ListNode* head2 = mid->next;
        mid->next = NULL;
        ListNode* l1 = mergeSort(head);
        ListNode* l2 = mergeSort(head2);
        return merge(l1, l2);
    }
};
```

注意点

- 快慢指针 判断 fast 及 fast.Next 是否为 nil 值
- 递归 mergeSort 需要断开中间节点
- 递归返回条件为 head 为 nil 或者 head.Next 为 nil

### [reorder-list](https://leetcode-cn.com/problems/reorder-list/)

> 给定一个单链表  *L*：*L*→*L*→…→*L\_\_n*→*L*
> 将其重新排列后变为： *L*→*L\_\_n*→*L*→*L\_\_n*→*L*→*L\_\_n*→…

思路：找到中点断开，翻转后面部分，然后合并前后两个链表

```c++
class Solution {
public:
    void reorderList(ListNode* head) {
        //find mid
        if(head == NULL)
            return ;
        ListNode* slow = head;
        ListNode* fast = head->next;
        while(fast != NULL && fast -> next != NULL)
        {
            slow = slow -> next;
            fast = fast -> next -> next;
        }

        //reverse the last half list
        ListNode* last = NULL;
        ListNode* cur = slow->next;
        slow -> next = NULL;
        while(cur != NULL)
        {
            ListNode* tp = cur -> next;
            cur->next = last;
            last = cur;
            cur = tp;
        }

        //merge two list
        ListNode* root = new ListNode;
        cur = root;
        bool odd = 1;
        while(head != NULL && last != NULL)
        {
            if(odd)
            {
                cur->next = head;
                head = head->next;
            }
            else
            {
                cur->next = last;
                last = last ->next;
            }
            odd = !odd;
            cur = cur->next;
        }
        if(head)
            cur->next = head;
        else
            cur->next = last;
    }
};
```

### [linked-list-cycle](https://leetcode-cn.com/problems/linked-list-cycle/)

> 给定一个链表，判断链表中是否有环。

思路：快慢指针，快慢指针相同则有环，证明：如果有环每走一步快慢指针距离会减 1
![fast_slow_linked_list](https://img.fuiboom.com/img/fast_slow_linked_list.png)

```c++
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head->next;
        while(fast != NULL && fast->next != NULL)
        {
            if(fast == slow )
                return 1;
            slow = slow -> next;
            fast = fast -> next -> next;
        }
        return 0;
    }
};
```

### [linked-list-cycle-ii](https://leetcode-cn.com/problems/linked-list-cycle-ii/)

> 给定一个链表，返回链表开始入环的第一个节点。  如果链表无环，则返回  `null`。

思路：快慢指针，快慢相遇之后，慢指针回到头，快慢指针步调一致一起移动，相遇点即为入环点
![cycled_linked_list](https://img.fuiboom.com/img/cycled_linked_list.png)

```c++
func detectCycle(head *ListNode) *ListNode {
    // 思路：快慢指针，快慢相遇之后，慢指针回到头，快慢指针步调一致一起移动，相遇点即为入环点
    if head == nil {
        return head
    }
    fast := head.Next
    slow := head

    for fast != nil && fast.Next != nil {
        if fast == slow {
            // 慢指针重新从头开始移动，快指针从第一次相交点下一个节点开始移动
            fast = head
            slow = slow.Next // 注意
            // 比较指针对象（不要比对指针Val值）
            for fast != slow {
                fast = fast.Next
                slow = slow.Next
            }
            return slow
        }
        fast = fast.Next.Next
        slow = slow.Next
    }
    return nil
}
```

坑点

- 指针比较时直接比较对象，不要用值比较，链表中有可能存在重复值情况
- 第一次相交后，快指针需要从下一个节点开始和头指针一起匀速移动

另外一种方式是 fast=head,slow=head

这两种方式不同点在于，**一般用 fast=head.Next 较多**，因为这样可以知道中点的上一个节点，可以用来删除等操作。

- fast 如果初始化为 head.Next 则中点在 slow.Next
- fast 初始化为 head,则中点在 slow

### [palindrome-linked-list](https://leetcode-cn.com/problems/palindrome-linked-list/)

> 请判断一个链表是否为回文链表。

```c++
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode* last = NULL;
        ListNode* slow = head;
        ListNode* tp = slow -> next;
        ListNode* fast = head->next;
        while(fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            tp = slow->next;
            slow->next = last;
            last = slow;
            slow = tp;
        }
        if(fast)
        {
            tp = slow->next;
            slow->next = last;
            last = slow;
            slow = tp;
        }
        else
            slow = slow->next;
        while(slow != NULL)
        {
            if(slow -> val != last -> val)
                return 0;
            slow = slow->next;
            last = last->next;
        }
        return 1;
    }
};
```

### [copy-list-with-random-pointer](https://leetcode-cn.com/problems/copy-list-with-random-pointer/)

> 给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。
> 要求返回这个链表的 深拷贝。

思路：1、每个结点后插入其自身一次；2、结点拷贝的random向后挪一位；3、将链表复原并将复制的结点抽出

```c++
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == NULL)
            return NULL;
        bool ist = 0;
        Node* cur = head;
        while(cur != NULL)
        {
            Node* tp = new Node(cur->val);
            tp->next = cur->next;
            tp->random = cur->random;
            cur->next = tp;
            cur = tp->next;
        }
        cur = head;
        while(cur != NULL)
        {
            if(ist)
                if(cur->random)
                    cur->random = cur->random->next;
            cur = cur->next;
            ist = !ist;
        }
        Node* root = new Node(-1);
        cur = root;
        Node* head2 = head->next;
        while(1)
        {
            cur->next = head2;
            head->next = head2->next;
            head  = head -> next;
            if(head == NULL)
                break;
            head2 = head2 -> next -> next;
            cur = cur->next;
        }
        return root->next;
    }
};
```

## 总结

链表必须要掌握的一些点，通过下面练习题，基本大部分的链表类的题目都是手到擒来~

- null/nil 异常处理
- dummy node 哑巴节点
- 快慢指针
- 插入一个节点到排序链表
- 从一个链表中移除一个节点
- 翻转链表
- 合并两个链表
- 找到链表的中间节点

## 练习

- [x] [remove-duplicates-from-sorted-list](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)
- [x] [remove-duplicates-from-sorted-list-ii](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/)
- [x] [reverse-linked-list](https://leetcode-cn.com/problems/reverse-linked-list/)
- [x] [reverse-linked-list-ii](https://leetcode-cn.com/problems/reverse-linked-list-ii/)
- [x] [merge-two-sorted-lists](https://leetcode-cn.com/problems/merge-two-sorted-lists/)
- [x] [partition-list](https://leetcode-cn.com/problems/partition-list/)
- [x] [sort-list](https://leetcode-cn.com/problems/sort-list/)
- [x] [reorder-list](https://leetcode-cn.com/problems/reorder-list/)
- [x] [linked-list-cycle](https://leetcode-cn.com/problems/linked-list-cycle/)
- [x] [linked-list-cycle-ii](https://leetcode-cn.com/problems/linked-list-cycle-ii/)
- [x] [palindrome-linked-list](https://leetcode-cn.com/problems/palindrome-linked-list/)
- [x] [copy-list-with-random-pointer](https://leetcode-cn.com/problems/copy-list-with-random-pointer/)
