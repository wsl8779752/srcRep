int reverse(int x) {
   
    int digit,oldx,reminder;   
    for (digit = 0 ,oldx=0; x ;oldx=digit, x/=10){
        reminder = x%10;   
        digit *=10;
        digit += reminder;  
        if(digit/10 != oldx) return 0;
    }   
    return digit ;
}
