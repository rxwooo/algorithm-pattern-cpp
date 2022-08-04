#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

vector<int> result;

void preorderTraversal(TreeNode *root)
{
    if (root == NULL)
        return;
    result.push_back(root->val);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void preorderTraversal(TreeNode *root)
{
    if (root == NULL)
        return;
    stack<TreeNode *> call;
    call.push(root);
    while (call.size() != 0)
    {
        TreeNode *cur = call.top();
        call.pop();
        if (cur)
        {
            if (cur->right)
                call.push(cur->right);
            if (cur->left)
                call.push(cur->left);
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

void inorderTraversal(TreeNode *root)
{
    if (root == NULL)
        return;
    stack<TreeNode *> call;
    call.push(root);
    while (call.size() != 0)
    {
        TreeNode *cur = call.top();
        call.pop();
        if (cur)
        {
            if (cur->right)
                call.push(cur->right);
            call.push(cur);
            call.push(NULL);
            if (cur->left)
                call.push(cur->left);
        }
        else
        {
            result.push_back(call.top()->val);
            call.pop();
        }
    }
}

void postorderTraversal(TreeNode *root)
{
    if (root = NULL)
        return;
    stack<TreeNode *> call;
    call.push(root);
    while (call.size() != 0)
    {
        TreeNode *cur = call.top();
        call.pop();
        if (cur)
        {
            call.push(cur);
            call.push(NULL);
            if (cur->right)
                call.push(cur->right);
            if (cur->left)
                call.push(cur->left);
        }
        else
        {
            result.push_back(call.top()->val);
            call.pop();
        }
    }
}

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

vector<vector<int>> res;
void addVector(TreeNode *root, int level)
{
    if (root == NULL)
        return;
    if (res.size() == level)
        res.push_back(vector<int>());
    res[level].push_back(root->val);
    addVector(root->left, level + 1);
    addVector(root->right, level + 1);
}

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

int main()
{

    return 0;
}