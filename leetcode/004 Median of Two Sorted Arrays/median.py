class Solution(object):
    def findMedianSortedArrays(self, nums1, nums2):
    """
    :type nums1: List[int]
    :type nums2: List[int]
    :rtype: float
    """
    m , n = len(nums1) ,len(nums2)
    if m > n :
    nums1 , nums2 , m , n = nums2 , nums1 , n , m

    if n == 0 :
    raise ValueError

    imin , imax , half_len =  0, m , (m+n+1)/2 
    while imin <= imax:
        i = (imin+imax)/2
        j = half_len - i
        if i > 0 and nums1[i-1] > nums2[ j ] :
            imax = imax - 1
        elif i < m and nums1[i] < nums2[j-1] :
            imin = imin + 1
        else :
            # i is perfect
            # calculate max_left
        if   i == 0 :  max_left = nums2[j-1]
        elif j == 0 :  max_left = nums1[i-1]
        else :         max_left = max( nums1[i-1] , nums2[j-1] )

        if (m+n)%2 == 1 :
        return max_left

        if   i == m :   min_right = nums2[j]
        elif j == n :   min_right = nums1[i]
        else :          min_right = min( nums1[i] , nums2[j] )
                    
        return ( max_left + min_right ) /2.0
