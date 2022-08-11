# 排序

## 常考排序

### 快速排序

```c++
int partition(vector<int>& nums, int left, int right)
{
    int less = left;
    int randNum = (rand() % (right - left + 1)) + left;
    swap(nums[randNum], nums[right]);
    int target = nums[right];
    for(int i = left; i < right; i++)
        if(nums[i] < target)
            swap(nums[i], nums[less++]);
    swap(nums[right], nums[less]);
    return less;
}

void quickSort(vector<int>& nums, int left, int right)
{
    if(left >= right)
        return ;
    int devide = partition(nums, left, right);
    quickSort(nums, left, devide -1);
    quickSort(nums, devide + 1, right);
}
```

### 归并排序

```c++
void merge(vector<int>& nums, int left, int mid, int right)
{
    int pos1 = left;
    int pos2 = mid + 1;
    vector<int> temp(right - left + 1);
    int pos = 0;
    while(pos1 <= mid && pos2 <= right)
        temp[pos++] = nums[pos1] < nums[pos2]? nums[pos1++]: nums[pos2++];
    while(pos1 <= mid)
        temp[pos++] = nums[pos1++];
    while(pos2 <= right)
        temp[pos++] = nums[pos2++];
    for(int i = left; i <= right; i++)
        nums[i] = temp[i - left];
}

void mergeSort(vector<int>& nums, int left, int right)
{
    if(left >= right)
        return ;
    int mid = left + (right - left) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid + 1, right);
    merge(nums, left, mid, right);
}
```

### 堆排序

用数组表示的完美二叉树 complete binary tree

> 完美二叉树 VS 其他二叉树

![image.png](https://img.fuiboom.com/img/tree_type.png)

[动画展示](https://www.bilibili.com/video/av18980178/)

![image.png](https://img.fuiboom.com/img/heap.png)

核心代码

```c++
void heapify(vector<int>& nums, int index, int heapsize)
{
    int left  = index * 2 + 1;
    int right = index * 2 + 2;
    int maxN  = index;

    if(left < heapsize && nums[maxN] < nums[left])
        maxN = left;
    if(right < heapsize && nums[maxN] < nums[right])
        maxN = right;
    if(maxN == index)
        return;
    swap(nums[index], nums[maxN]);
    heapify(nums, maxN, heapsize);
}

void heapInsert(vector<int>& nums, int index)
{
    while(index)
    {
        int pre = (index - 1) / 2;
        if(nums[pre] > nums[index])
            break;
        swap(nums[pre], nums[index]);
        index = pre;
    }
}

void HeapSort(vector<int>& nums)
{
    int heapsize = 0;
    int len = nums.size();
    while(heapsize < len)
        heapInsert(nums, heapsize++);
    while(heapsize)
    {
        swap(nums[--heapsize], nums[0]);
        heapify(nums, 0, heapsize);
    }
}

```

## 参考

[十大经典排序](https://www.cnblogs.com/onepixel/p/7674659.html)

[二叉堆](https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/er-cha-dui-xiang-jie-shi-xian-you-xian-ji-dui-lie)

## 练习

- [x] 手写快排、归并、堆排序
