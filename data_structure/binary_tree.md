# 二叉树

## 知识点

### 二叉树遍历

**前序遍历**：**先访问根节点**，再前序遍历左子树，再前序遍历右子树
**中序遍历**：先中序遍历左子树，**再访问根节点**，再中序遍历右子树
**后序遍历**：先后序遍历左子树，再后序遍历右子树，**再访问根节点**

注意点

- 以根访问顺序决定是什么遍历
- 左子树都是优先右子树

#### 前序递归

```c++
void preorderTraversal(Treenode* root)
{
    if(root == NULL)
        return ;
    result.push_back(root->val);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}
```

#### 前序非递归

```c++
void preorderTraversal(Treenode* root)
{
    if(root == NULL)
        return;
    stack<Treenode*> call;
    call.push(root);
    while(call.size() != 0)
    {
        Treenode* cur = call.top();
        call.pop();
        if(cur)
        {
            if(cur->right) call.push(cur->right);
            if(cur->left) call.push(cur->left);
            call.push(cur);
            call.push(NULL);
        }
        else
        {
            result.push_back(call.top()->val);
            call.pop();
        }
    }
}
```

#### 中序非递归

```c++
void inorderTraversal(Treenode* root)
{
    if(root == NULL)
        return ;
    stack<Treenode*> call;
    call.push(root);
    while (call.size() != 0)
    {
        Treenode* cur = call.top();
        call.pop();
        if(cur)
        {
            if(cur->right) call.push(cur->right);
            call.push(cur);
            call.push(NULL);
            if(cur->left) call.push(cur->left);
        }
        else
        {
            result.push_back(call.top()->val);
            call.pop();
        }
    } 
}
```

#### 后序非递归

```c++
void postorderTraversal(Treenode* root)
{
    if(root = NULL)
        return;
    stack<Treenode*> call;
    call.push(root);
    while(call.size() != 0)
    {
        Treenode* cur = call.top();
        call.pop();
        if(cur)
        {
            call.push(cur);
            call.push(NULL);
            if(cur->right) call.push(cur->right);
            if(cur->left) call.push(cur->left);
        }
        else
        {
            result.push_back(call.top()->val);
            call.pop();
        }
    }
}
```

注意点

- 核心就是：根节点必须在右节点弹出之后，再弹出

#### DFS 深度搜索-从上到下

```c++
//前序遍历
void preorderHelper(TreeNode *node){
    if(node == nullptr) return;
    result.push_back(node->val);
    preorderHelper(node->left);
    preorderHelper(node->right);
}

vector<int> preorderTraversal1(TreeNode* root) {
    preorderHelper(root);
    return result;
}
```

#### DFS 深度搜索-从下向上（分治法）

```c++
//前序遍历
vector<int> inorderTraversal(TreeNode *node){
    return divideAndConquer(node);
}

vector<int> divideAndConquer(TreeNode *node){
    vector<int> result;
    if (node == nullptr) {
        return result;
    }

    vector<int> left = divideAndConquer(node->left);
    vector<int> right = divideAndConquer(node->right);

    result.push_back(node->val);
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());

    return result;
}
```

注意点：

> DFS 深度搜索（从上到下） 和分治法区别：前者一般将最终结果通过指针参数传入，后者一般递归返回结果最后合并

#### BFS 层次遍历

```c++
vector<vector<int>> levelOrder(TreeNode* root)
{
    vector<vector<int>> result;
    if(root == NULL)
        return result;
    
    queue<TreeNode*> qu;
    qu.push(root);
    while (qu.size() != 0)
    {
        vector<int> level;
        int lsize = qu.size();
        while(lsize -- )
        {
            TreeNode* cur = qu.front();
            qu.pop();
            if(cur->left) qu.push(cur->left);
            if(cur->right) qu.push(cur->right);
            level.push_back(cur->val);
        }
        result.push_back(level);
    }
    return result;
}
```

### 分治法应用

先分别处理局部，再合并结果

适用场景

- 快速排序
- 归并排序
- 二叉树相关问题

分治法模板

- 递归返回条件
- 分段处理
- 合并结果

```c++
// 伪代码
class Solution {
    ResultType traversal(TreeNode root) {
        if (root == null) {
            // do something and return
        }

        // Divide
        ResultType left = traversal(root.left);
        ResultType right = traversal(root.right);

        // Conquer
        ResultType result = Merge from left and right

        return result;
    }
}
```

#### 典型示例

```c++
// V2：通过分治法遍历二叉树
class Solution {
    vector<int> preorderTraversal(TreeNode *root) {
        return divideAndConquer(root);
    }

    vector<int> divideAndConquer(TreeNode *node) {
        vector<int> result;
        if (node == nullptr) {
            return result;
        }
        // 分治
        vector<int> left = divideAndConquer(node->left);
        vector<int> right = divideAndConquer(node->right);
        // 合并结果
        result.push_back(node->val);
        result.insert(result.end(), left.begin(), left.end());
        result.insert(result.end(), right.begin(), right.end());
        return result;
    }
}
```

#### 归并排序  

```c++
class MergeSort
{
    void mergeSrot(vector<int>& nums, int start, int end)
    {
        if(nums.size() == 0)
            return ;
        if(start == end)
            return ;
        int mid = start + (end - start) / 2;

        mergeSrot(nums, start, mid);
        mergeSrot(nums, mid + 1, end);

        _merge(nums, start, mid, end);
    }

    void _merge(vector<int>& nums, int start, int mid, int end)
    {
        vector<int> temp(end - start + 1);
        int i = start;
        int j = mid + 1;
        int k = 0;
        while(i <= mid && j <= end)
            temp[k++] = nums[i] < nums[j]? nums[i++]: nums[j++];
        while(i <= mid)
            temp[k++] = nums[i++];
        while(j <= end)
            temp[k++] = nums[j++];
        for(int i = start; i <= end; i++)
            nums[i] = temp[i - start];
    }
};
```

注意点

> 递归需要返回结果用于合并

#### 快速排序  

```c++
class QuickSort
{
    void _quickSrot(vector<int>& nums, int begin, int end)
    {
        if(begin > end)
            return;
        int left = begin;
        int right = end;
        int key = nums[left];
        while(left < right)
        {
            while(left < right && nums[right] >= key)
                right --;
            nums[left] = right;

            while(left < right && nums[left] <= key)
                left ++;
            nums[right] = left;
        }
        nums[left] = key;
        _quickSrot(nums, begin, left);
        _quickSrot(nums, left + 1, end);
    }

    void quickSort(vector<int>& nums)
    {
        _quickSrot(nums, 0, nums.size() - 1);
    }
};
```

注意点：

> 快排由于是原地交换所以没有合并过程
> 传入的索引是存在的索引（如：0、length-1 等），越界可能导致崩溃

常见题目示例

#### maximum-depth-of-binary-tree

[maximum-depth-of-binary-tree](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)

> 给定一个二叉树，找出其最大深度。

思路：分治法

```c++
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root == NULL)
            return 0;
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        return max(right, left) + 1;
    }
};
```

#### balanced-binary-tree

[balanced-binary-tree](https://leetcode-cn.com/problems/balanced-binary-tree/)

> 给定一个二叉树，判断它是否是高度平衡的二叉树。

思路：分治法，左边平衡 && 右边平衡 && 左右两边高度 <= 1，
因为需要返回是否平衡及高度，要么返回两个数据，要么合并两个数据，
所以用-1 表示不平衡，>0 表示树高度（二义性：一个变量有两种含义）。

```c++
class Solution {
public:
    int _isBalanced(TreeNode* root)
    {
        if(root == NULL)
            return 0;
        int left = _isBalanced(root->left);
        int right = _isBalanced(root->right);

        if(left == -1 || right == -1) return -1;
        
        if(abs(right - left) < 2)
            return max(left, right) + 1;
        return -1;
    }

    bool isBalanced(TreeNode* root) {
        return _isBalanced(root) != -1;
    }
};
```

注意

> 一般工程中，结果通过两个变量来返回，不建议用一个变量表示两种含义

#### binary-tree-maximum-path-sum

[binary-tree-maximum-path-sum](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)

> 给定一个**非空**二叉树，返回其最大路径和。

思路：分治法，分为三种情况：左子树最大路径和最大，右子树最大路径和最大，左右子树最大加根节点最大，需要保存两个变量：一个保存子树最大路径和，一个保存左右加根节点和，然后比较这个两个变量选择最大值即可

```c++
class Solution {
public:
    int max_path = 0xc0c0c0c0;
    int maxPathSum(TreeNode* root) {
        return max(path(root), max_path);
    }

    int path(TreeNode* root)
    {
        if(root == NULL)
            return 0;
        int left = max(path(root->left), 0);
        int right = max(path(root->right), 0);

        max_path = max(max_path, root->val + left + right);
        return root->val + max(left, right);
    }
};
```

#### lowest-common-ancestor-of-a-binary-tree

[lowest-common-ancestor-of-a-binary-tree](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)

> 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

思路：分治法，有左子树的公共祖先或者有右子树的公共祖先，就返回子树的祖先，否则返回根节点

```c++
class Solution {
public:
    TreeNode* res = NULL;
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        findChild(root, p, q);
        return res;
    }

    bool findChild(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if(root == NULL)
            return 0 ;
        bool cur = 0;
        if(root == p || root == q)
            cur = 1;
        bool left = findChild(root->left, p, q);
        bool right = findChild(root->right, p, q);
        if(cur + left + right == 2)
            res = root;
        return left + right + cur;
    }
};
```

### BFS 层次应用

#### binary-tree-level-order-traversal

[binary-tree-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)

> 给你一个二叉树，请你返回其按  **层序遍历**  得到的节点值。 （即逐层地，从左到右访问所有节点）

思路：用一个队列记录一层的元素，然后扫描这一层元素添加下一层元素到队列（一个数进去出来一次，所以复杂度 O(logN)）

```c++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(root == NULL)
            return res;

        queue<TreeNode*> qu;
        qu.push(root);
        while(qu.size())
        {
            int len = qu.size();
            vector<int> level;
            while(len --)
            {
                TreeNode* tp = qu.front();
                qu.pop();
                level.push_back(tp->val);
                if(tp->left) qu.push(tp->left);
                if(tp->right) qu.push(tp->right);
            }
            res.push_back(level);
        }
        return res;
    }
};
```

#### binary-tree-level-order-traversal-ii

[binary-tree-level-order-traversal-ii](https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/)

> 给定一个二叉树，返回其节点值自底向上的层次遍历。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

思路：在层级遍历的基础上，翻转一下结果即可(此处代码为递归版)

```c++
class Solution {
public:
    vector<vector<int>> tra;
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        levelTra(root, 0);
        reverse(tra.begin(), tra.end());
        return tra;
    }

    void levelTra(TreeNode* root, int level)
    {
        if(root == NULL)
            return ;
        if(tra.size() < level + 1)
            tra.push_back({});
        
        levelTra(root->left, level + 1);
        levelTra(root->right, level + 1);

        tra[level].push_back(root->val);
    }
};
```

#### binary-tree-zigzag-level-order-traversal

[binary-tree-zigzag-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/)

> 给定一个二叉树，返回其节点值的锯齿形层次遍历。Z 字形遍历

```c++
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        queue<TreeNode*> nodequ;

        bool reverse = 0;
        if(root)
            nodequ.push(root);
        while(nodequ.size())
        {
            int len = nodequ.size();
            vector<int> level(len, 0);
            for(int i = 0; i < len; i++)
            {
                int pos = reverse? len - i - 1: i;
                TreeNode* node = nodequ.front();
                nodequ.pop();
                level[pos] = node->val;
                if(node->left) nodequ.push(node->left);
                if(node->right) nodequ.push(node->right);
            }
            ans.push_back(level);
            reverse = !reverse;
        }
        return ans;
    }
};
```

### 二叉搜索树应用

#### validate-binary-search-tree

[validate-binary-search-tree](https://leetcode-cn.com/problems/validate-binary-search-tree/)

> 给定一个二叉树，判断其是否是一个有效的二叉搜索树。

思路 1：中序遍历，检查结果列表是否已经有序

思路 2：分治法，判断左 MAX < 根 < 右 MIN

```c++
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if(root == NULL)
            return 1;
        
        int lastNum;
        bool first = 1;
        stack<TreeNode*> call;
        call.push(root);
        while(call.size())
        {
            TreeNode* cur = call.top();
            call.pop();
            if(cur)
            {
                if(cur->left) call.push(cur->left);
                call.push(cur);
                call.push(NULL);
                if(cur->right) call.push(cur->right);
            }
            else
            {
                int curNum = call.top()->val;
                call.pop();
                if(first)
                {
                    lastNum = curNum;
                    first = 0;
                }
                else
                {
                    if(curNum >= lastNum) return 0;
                    lastNum = curNum;
                }
            }
        }
        return 1;
    }
};


```


#### insert-into-a-binary-search-tree

[insert-into-a-binary-search-tree](https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/)

> 给定二叉搜索树（BST）的根节点和要插入树中的值，将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。

思路：找到最后一个叶子节点满足插入条件即可

```c++
// DFS查找插入位置
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root == NULL)
            return new TreeNode(val);
        
        if(root->val < val){
           root->right = insertIntoBST(root->right, val);
        }else{
           root->left = insertIntoBST(root->left ,val);
        }
        return root;
    }
};
```

## 总结

- 掌握二叉树递归与非递归遍历
- 理解 DFS 前序遍历与分治法
- 理解 BFS 层次遍历

## 练习

- [x] [maximum-depth-of-binary-tree](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)
- [x] [balanced-binary-tree](https://leetcode-cn.com/problems/balanced-binary-tree/)
- [x] [binary-tree-maximum-path-sum](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/)
- [x] [lowest-common-ancestor-of-a-binary-tree](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)
- [x] [binary-tree-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)
- [x] [binary-tree-level-order-traversal-ii](https://leetcode-cn.com/problems/binary-tree-level-order-traversal-ii/)
- [x] [binary-tree-zigzag-level-order-traversal](https://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal/)
- [x] [validate-binary-search-tree](https://leetcode-cn.com/problems/validate-binary-search-tree/)
- [x] [insert-into-a-binary-search-tree](https://leetcode-cn.com/problems/insert-into-a-binary-search-tree/)
