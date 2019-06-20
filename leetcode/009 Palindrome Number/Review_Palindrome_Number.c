bool isPalindrome(int x) {
    int reverse_num ;
    if ( x < 0 || ( x!=0 && x%10 ==0) ) return false;   
    reverse_num = 0 ;
    while( reverse_num < x ){
        reverse_num = reverse_num*10 + x%10;
        x/=10 ;
    }
    return reverse_num==x || reverse_num/10==x ; 

}
