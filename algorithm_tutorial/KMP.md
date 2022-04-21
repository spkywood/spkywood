# KMP 字符串匹配算法

> 问题：找到一个字符串在另一个字符串中出现的位置索引，如果没有出现输出-1；

## 暴力解法

暴力解法即，从头开始找第一个匹配到的字符串

```java
public class SubString {
    public int subString(String str, String sub) {
        // 子串长度较小
        if (sub.length() > str.length()) return -1;
        for (int i = 0; i < str.length(); i++) {
            for (int j = 0; j < sub.length(); j++) {
                if (str.charAt(i+j) != sub.charAt(j)) break;
                if (j == sub.length()-1) return i;
            }
        }
        return -1;
    }
}
```

## 部分匹配表 pmt

- 前缀：最后一个字符以外，一个字符串的全部头部组合

- 后缀：一个字符以外，一个字符串的全部尾部组合。

"部分匹配值"就是"前缀"和"后缀"的最长的共有元素的长度。以"ABCDABD"为例，

![PMT](../images/kmp_pmt.png)

```
－　"A"的前缀和后缀都为空集，共有元素的长度为0；

－　"AB"的前缀为[A]，后缀为[B]，共有元素的长度为0；

－　"ABC"的前缀为[A, AB]，
    后缀为[BC, C]，共有元素的长度0；

－　"ABCD"的前缀为[A, AB, ABC]，
    后缀为[BCD, CD, D]，共有元素的长度为0；

－　"ABCDA"的前缀为[A, AB, ABC, ABCD]，
    后缀为[BCDA, CDA, DA, A]，共有元素为"A"，长度为1；

－　"ABCDAB"的前缀为[A, AB, ABC, ABCD, ABCDA]，
    后缀为[BCDAB, CDAB, DAB, AB, B]，共有元素为"AB"，长度为2；

－　"ABCDABD"的前缀为[A, AB, ABC, ABCD, ABCDA, ABCDAB]，
    后缀为[BCDABD, CDABD, DABD, ABD, BD, D]，共有元素的长度为0。
```

如何构造部分匹配表？

```c++
// c++版
void pmt(const char p[], int next[]) {
	int m = strlen(p);
	next[0] = 0;
	for (int i=1, k=0; i<m; ++i) // i是p字符串下标,k是已匹配的长度
	{
		while(k > 0 && p[i] != p[k])
		{
			k = next[k-1];      
            // 部分匹配不相同时，回溯减少已匹配的长度。
            // 例如 abcabcd -> 0001230 当i==6时，k==3，依次减少3-2-1-0
		}

		if(p[i] == p[k])
		{
			k++;    // dp的思想，之前匹配的长度+1；
		}
		next[i] = k;
	}
}
```

## 字符串匹配移动

> 移动位数 = 已匹配字符数 - 部分匹配值

例如下图中移动情况：

![移动位数](../images/kmp_move.png)

已匹配的字符为 `ABCDBA` 为 `6`，部分匹配表中的值为 `2`，移动位数为 `6 - 2 = 4`。

参考：

[KMP 算法详细解析](https://blog.sengxian.com/algorithms/kmp)

[字符串匹配的KMP算法](http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html)