# 栈和队列

## 简介

栈的特点是后入先出

![image.png](https://img.fuiboom.com/img/stack.png)

根据这个特点可以临时保存一些数据，之后用到依次再弹出来，常用于 DFS 深度搜索

队列一般常用于 BFS 广度搜索，类似一层一层的搜索

## Stack 栈

[min-stack](https://leetcode-cn.com/problems/min-stack/)

> 设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。

思路：每次入栈都分别压入当前值与当前最小值

```c++
class MinStack {
public:
    stack<int> _stack;

    MinStack() {

    }
    
    void push(int val) {
        int minN;
        if(_stack.empty())
            minN = val;
        else
            minN = min(_stack.top(), val);
        _stack.push(val);
        _stack.push(minN);
    }
    
    void pop() {
        _stack.pop();
        _stack.pop();
    }
    
    int top() {
        if(_stack.empty())
            return _stack.top();
        int minN = _stack.top();
        _stack.pop();
        int res = _stack.top();
        _stack.push(minN);
        return res;
    }
    
    int getMin() {
        return _stack.top();
    }
};
```

[evaluate-reverse-polish-notation](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/)

> **波兰表达式计算** > **输入:** `["2", "1", "+", "3", "*"]` > **输出:** 9
>
> **解释:** `((2 + 1) * 3) = 9`

思路：通过栈保存原来的元素，遇到表达式弹出运算，再推入结果，重复这个过程

```c++
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        int len = tokens.size();
        stack<int> _stack;
        for(int i = 0; i < len; i ++)
        {
            if(tokens[i].size() > 1 || _stack.size() < 2)
                _stack.push(stoi(tokens[i]));
            else
            {
                if(tokens[i][0] >= '0' && tokens[i][0] <= '9')
                    _stack.push(tokens[i][0] - '0');
                else
                {
                    int b = _stack.top();
                    _stack.pop();
                    int a = _stack.top();
                    _stack.pop();

                    if(tokens[i][0] == '+')
                        _stack.push(a + b);
                    else if(tokens[i][0] == '-')
                        _stack.push(a - b);
                    else if(tokens[i][0] == '*')
                        _stack.push(a * b);
                    else if(tokens[i][0] == '/')
                        _stack.push(a / b);
                }
            }
        }
        return _stack.top();
    }
};
```

[decode-string](https://leetcode-cn.com/problems/decode-string/)

> 给定一个经过编码的字符串，返回它解码后的字符串。
> s = "3[a]2[bc]", 返回 "aaabcbc".
> s = "3[a2[c]]", 返回 "accaccacc".
> s = "2[abc]3[cd]ef", 返回 "abcabccdcdcdef".

思路：通过栈辅助进行操作

```c++
class Solution {
public:
    string decodeString(string s) {
        int len = s.size();
        stack<char> tp;
        deque<char> deq;
        string res;
        for(int i = 0 ; i< len; i++)
        {
            if(s[i] != ']')
                deq.push_back(s[i]);
            else
            {
                char c = deq.back();
                while(c != '[')
                {
                    deq.pop_back();
                    tp.push(c);
                    c = deq.back();
                }
                deq.pop_back();

                int digit = 0;
                int k = 0;
                char num = deq.back();
                while(num >= '0' && num <= '9')
                {
                    k += (deq.back() - '0') * pow(10, digit++);
                    deq.pop_back();
                    if(deq.empty())
                        break;
                    num = deq.back();
                }

                string tpStr;
                while(tp.size() != 0)
                {
                    tpStr += tp.top();
                    tp.pop();
                }
                
                while(k--)
                    for(int i = 0; i < tpStr.size(); i++)
                        deq.push_back(tpStr[i]);
            }
        }
        while(deq.size())
        {
            res += deq.front();
            deq.pop_front();
        }
        return res;
    }
};
```

[binary-tree-inorder-traversal](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)

> 给定一个二叉树，返回它的*中序*遍历。

```c++
// 思路：通过stack 保存已经访问的元素，用于原路返回
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root == NULL)
            return res;
        stack<TreeNode*> _stack;
        _stack.push(root);
        while(_stack.size())
        {
            TreeNode* cur = _stack.top();
            _stack.pop();
            if(cur)
            {
                if(cur->right) _stack.push(cur->right);
                _stack.push(cur);
                _stack.push(NULL);
                if(cur->left) _stack.push(cur->left);
            }
            else
            {
                res.push_back(_stack.top() -> val);
                _stack.pop();
            }
        }
        return res;
    }
};
```

[clone-graph](https://leetcode-cn.com/problems/clone-graph/)

> 给你无向连通图中一个节点的引用，请你返回该图的深拷贝（克隆）。

```c++
class Solution {
public:
    unordered_map<Node*, Node*> _map;
    Node* cloneGraph(Node* node) {
        if(node == NULL)
            return NULL;
        if(_map.find(node) != _map.end())
            return _map[node];
        Node* newNode = new Node(node->val);
        _map.insert({node, newNode});
        int len = node->neighbors.size();
        for(int i = 0; i < len; i++)
        {
            Node* tp = cloneGraph(node->neighbors[i]);
            newNode->neighbors.push_back(tp);
        }
        return newNode;
    }
};
```

[number-of-islands](https://leetcode-cn.com/problems/number-of-islands/)

> 给定一个由  '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。

思路：通过深度搜索遍历可能性（注意标记已访问元素）

```c++
class Solution {
public:
    int row, col;
    int numIslands(vector<vector<char>>& grid) {
        row = grid.size();
        col = grid[0].size();
        int count = 0;
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
                if(grid[i][j] == '1')
                {
                    count ++;
                    dfs(i, j, grid);
                }
            }
        }
        return count;
    }
    void dfs(int x, int y, vector<vector<char>>& grid)
    {
        if(x < 0 || y < 0 || x == row || y == col)
            return;
        if(grid[x][y] == '0' || grid[x][y] == '2')
            return;
        grid[x][y] = '2';
        dfs(x + 1, y, grid);
        dfs(x, y + 1, grid);
        dfs(x - 1, y, grid);
        dfs(x, y - 1, grid);
        return;
    }
};
```

[largest-rectangle-in-histogram](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)

> 给定 _n_ 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
> 求在该柱状图中，能够勾勒出来的矩形的最大面积。

思路：求以当前柱子为高度的面积，即转化为寻找小于当前值的左右两边值

![image.png](https://img.fuiboom.com/img/stack_rain.png)

用栈保存小于当前值的左的元素

![image.png](https://img.fuiboom.com/img/stack_rain2.png)

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0);
        stack<int> _stack;
        int len = heights.size();
        int area = 0;
        for(int i = 0; i < len; i ++)
        {
            while(!_stack.empty() && heights[i] < heights[_stack.top()])
            {
                int h = heights[_stack.top()];
                _stack.pop();
                int w = _stack.empty()? i: (i - _stack.top() - 1);
                area = max(area, h * w);
            }
            _stack.push(i);
        }
        return area;
    }
};
```

## Queue 队列

常用于 BFS 宽度优先搜索

[implement-queue-using-stacks](https://leetcode-cn.com/problems/implement-queue-using-stacks/)

> 使用栈实现队列

```c++
class MyQueue {
public:
    stack<int> in;
    stack<int> out;
    MyQueue() {

    }
    
    void push(int x) {
        in.push(x);
    }
    
    int pop() {
        if(out.empty())
        {
            while(!in.empty())
            {
                out.push(in.top());
                in.pop();
            }
        }
        int res = out.top();
        out.pop();
        return res;
    }
    
    int peek() {
        int res = this->pop();
        out.push(res);
        return res;
    }
    
    bool empty() {
        return out.empty() && in.empty();
    }
};
```

二叉树层次遍历

```c++
vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> result;
    if (root == NULL)
        return result;

    queue<TreeNode *> qu;
    qu.push(root);
    while (qu.size() != 0)
    {
        vector<int> level;
        int lsize = qu.size();
        while (lsize--)
        {
            TreeNode *cur = qu.front();
            qu.pop();
            if (cur->left)
                qu.push(cur->left);
            if (cur->right)
                qu.push(cur->right);
            level.push_back(cur->val);
        }
        result.push_back(level);
    }
    return result;
}
```

[01-matrix](https://leetcode-cn.com/problems/01-matrix/)

> 给定一个由 0 和 1 组成的矩阵，找出每个元素到最近的 0 的距离。
> 两个相邻元素间的距离为 1

```c++
// BFS 从0进队列，弹出之后计算上下左右的结果，将上下左右重新进队列进行二层操作
// 0 0 0 0
// 0 x 0 0
// x x x 0
// 0 x 0 0

// 0 0 0 0
// 0 1 0 0
// 1 x 1 0
// 0 1 0 0

// 0 0 0 0
// 0 1 0 0
// 1 2 1 0
// 0 1 0 0
class Solution
{
public:
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {
        queue<vector<int>> qu;
        int h = mat.size();
        int w = mat[0].size();
        vector<vector<int>> res(h, vector<int>(w));

        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                if (mat[i][j] == 0)
                    qu.push({i, j});

        vector<vector<int>> move = {{0, 0, 1, -1}, {1, -1, 0, 0}};
        int len = move[0].size();
        while (qu.size())
        {
            vector<int> cur = qu.front();
            qu.pop();
            for (int i = 0; i < len; i++)
            {
                int row = cur[0] + move[0][i];
                int col = cur[1] + move[1][i];
                if (row >= 0 && row < h && col >= 0 && col < w)
                    if (mat[row][col] && !res[row][col])
                    {
                        qu.push({row, col});
                        res[row][col] = res[cur[0]][cur[1]] + 1;
                    }
            }
        }
        return res;
    }
};
```

## 总结

- 熟悉栈的使用场景
  - 后入先出，保存临时值
  - 利用栈 DFS 深度搜索
- 熟悉队列的使用场景
  - 利用队列 BFS 广度搜索

## 练习

- [x] [min-stack](https://leetcode-cn.com/problems/min-stack/)
- [x] [evaluate-reverse-polish-notation](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/)
- [x] [decode-string](https://leetcode-cn.com/problems/decode-string/)
- [x] [binary-tree-inorder-traversal](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)
- [x] [clone-graph](https://leetcode-cn.com/problems/clone-graph/)
- [x] [number-of-islands](https://leetcode-cn.com/problems/number-of-islands/)
- [x] [largest-rectangle-in-histogram](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)
- [x] [implement-queue-using-stacks](https://leetcode-cn.com/problems/implement-queue-using-stacks/)
- [x] [01-matrix](https://leetcode-cn.com/problems/01-matrix/)
