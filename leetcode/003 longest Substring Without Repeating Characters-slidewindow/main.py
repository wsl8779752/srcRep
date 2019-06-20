class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        hashmap = {}
        i = 0
        ans = 0
        for j in range( len(s)) :
            if s[j] in hashmap:
            i = max(i,hashmap[s[j]]+1)

            hashmap[ s[j] ] = j
            ans = max(ans, j-i+1)

    return ans 
