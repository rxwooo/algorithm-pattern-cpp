# 二进制

## 常见二进制操作

### 基本操作

a=0^a=a^0

0=a^a

由上面两个推导出：a=a^b^b

### 交换两个数

a=a^b

b=a^b

a=a^b

### 移除最后一个 1

a=n&(n-1)

### 获取最后一个 1

diff=(n&(n-1))^n

## 常见题目

[single-number](https://leetcode-cn.com/problems/single-number/)

> 给定一个**非空**整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        if(nums.size() == 1)
            return nums[0];
        for(int i = 1; i < nums.size(); i++)
            nums[i] ^= nums[i - 1]; 
        return nums.back();
    }
};
```

[single-number-ii](https://leetcode-cn.com/problems/single-number-ii/)

> 给定一个**非空**整数数组，除了某个元素只出现一次以外，其余每个元素均出现了三次。找出那个只出现了一次的元素。

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for(int i = 0; i < 32; i++)
        {
            int tp = 0;
            for(int j = 0; j < nums.size(); j++)
                tp += ((nums[j] >> i) & 1);
            tp %= 3;
            if(tp != 0)
                res += (1 << i);
        }
        return res;
    }
};
```

[single-number-iii](https://leetcode-cn.com/problems/single-number-iii/)

> 给定一个整数数组  `nums`，其中恰好有两个元素只出现一次，其余所有元素均出现两次。 找出只出现一次的那两个元素。

```c++
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int tp1 = 0;
        int tp2 = 0;
        for(int num: nums)
            tp1 ^= num;
        int bit = 0;
        for(int i = 0; i < 32; i++)
            if((tp1 >> i) & 1)
            {
                bit = i;
                break;
            }
        for(int num: nums)
            if((num >> bit) & 1)
                tp2 ^= num;
        tp1 ^= tp2;
        return {tp1, tp2};
    }
};
```

[number-of-1-bits](https://leetcode-cn.com/problems/number-of-1-bits/)

> 编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为 ‘1’  的个数（也被称为[汉明重量](https://baike.baidu.com/item/%E6%B1%89%E6%98%8E%E9%87%8D%E9%87%8F)）。

```c++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        while(n)
        {
            count ++;
            n &= (n - 1);
        }
        return count;
    }
};
```

[counting-bits](https://leetcode-cn.com/problems/counting-bits/)

> 给定一个非负整数  **num**。对于  0 ≤ i ≤ num  范围中的每个数字  i ，计算其二进制数中的 1 的数目并将它们作为数组返回。

```c++
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> res(n+1);
        res[0] = 0;
        for(int i = 1 ; i <= n; i++ )
            res[i] = res[i&(i - 1)] + 1;
        return res;
    }
};
```

[reverse-bits](https://leetcode-cn.com/problems/reverse-bits/)

> 颠倒给定的 32 位无符号整数的二进制位。

思路：依次颠倒即可

```c++
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for(int i = 0 ; i < 32; i++)
            res += ((n >> i) & 1) * (1 << (31 - i));
        return res;
    }
};
```

[bitwise-and-of-numbers-range](https://leetcode-cn.com/problems/bitwise-and-of-numbers-range/)

> 给定范围 [m, n]，其中 0 <= m <= n <= 2147483647，返回此范围内所有数字的按位与（包含 m, n 两端点）。

```c++
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int offset = 0;
        while(left != right)
        {
            left >>= 1;
            right >>= 1;
            offset ++;
        }
        return left << offset;
    }
};
```

## 练习

- [x] [single-number](https://leetcode-cn.com/problems/single-number/)
- [x] [single-number-ii](https://leetcode-cn.com/problems/single-number-ii/)
- [x] [single-number-iii](https://leetcode-cn.com/problems/single-number-iii/)
- [x] [number-of-1-bits](https://leetcode-cn.com/problems/number-of-1-bits/)
- [x] [counting-bits](https://leetcode-cn.com/problems/counting-bits/)
- [x] [reverse-bits](https://leetcode-cn.com/problems/reverse-bits/)
