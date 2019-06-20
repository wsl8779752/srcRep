## [003 3. Longest Substring Without Repeating Characters-slide window](https://leetcode.com/problems/longest-substring-without-repeating-characters/description/)

Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.  　　

比较straint 的解决方式就一个滑动窗口（==sliding window==），滑动窗口可以理解为一种数据类型，例如S[i,j)从i开始，到j的字符串（不包括j）。 　　

那么问题变成了从i=0，j=0开始检查s[j]是否出现在 s[i,j）。如果s[j]不出现在s[i,j),j=j+1，等价于将slide window 右边界右移。持续判断直到出现s[j]被包含在s[i,j)中，此时i+1 然后继续判断S[j]，是否出现在s[i+1,j],重复执行上述操作，直到s[j]不包括在s[i,j)中 。然后j+1 继续判断。 可以用hash表来判断s[i,j）中是否包含s[j],这样每次查找的时间变为o(1)。总共的时间 是o（2n）。这已经是能想到的比较 靠谱的方法了。  

但有没有可能在优化呢？答案是肯定的，实际上每次我们i+1的目的就是要跳过之前出现的s[j‘]，并且使得i跳到j’+1的位置。那么既然这样，我们自然而然想到把位置记录在hash表里值里。   

如果我们知道 字符串是 ASIIC 的，那么可以直接 定义hashmap[128]作为哈希表。哈希表的值全部初始化为0.主循环里 从i=0，j=0开始到j《n位置 开始判断， s[j] 是否存在于哈希表中，如果不纯在j+1.如果存在使得 i = j+1 。但需要注意这样有时候会使得 i 变到 原先的i左边，这样有可能使得包括了原来的 重复字符串。所以i只能 是 取i 和 hash[s[j]] 的大值。 这样的算法即可。