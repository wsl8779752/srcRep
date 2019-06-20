void Adjust_heap(int *nums ,int parent,int len);
void sort_use_heap (int *nums ,int numsSize);

int** threeSum(int* nums, int numsSize, int* returnSize) {
    int begin ,l ,r,add_of_last_twonum,rest ;
    sort_use_heap(nums,numsSize);  //sort 
    if( numsSize < 3 ) return NULL;  
    int **ans = calloc(1,sizeof(int * ));
    
    add_of_last_twonum = nums[numsSize-2] + nums[numsSize-1];
    for( *returnSize= 0 ,begin = 0 ; begin < numsSize - 2 ; begin++){
        /*外循环中用了三个技巧来加速： 跳过重复值 ；假如num[begin] + num[end-2]+ num[end-1] < 0 ,说明
            3begin 太小，直接continue ；  假如num[begin] + num[bein+1] +num[begin+2] > 0 ,
            后续的数无论如何都找不到 =0，直接返回ans*/
        if( (begin && nums[begin] == nums[begin-1]) || ( nums[begin] + add_of_last_twonum < 0  ) ) continue ;
        l = begin+1 ,r = numsSize-1; 
        rest = - nums[begin];
        if( nums[begin+1] + nums[begin+2] > rest ) return ans ;           
        while( l < r ){
            if ( nums[l] + nums[r] < rest ) while ( ++l < r && nums[l] == nums[l-1] )  ; //内循环中跳过重复的值 
            else if( nums[l] + nums[r] > rest )  while ( l < --r && nums[r] == nums[r+1] )  ;
            else {
                 if( *returnSize )
                     ans = realloc(ans, sizeof(int *)*( *returnSize+1) ); /*（*returnSIze）最后自增，但分配ans[]在前，所以要申请*returnSize+1 长度内存 */
                 ans[*returnSize]  = malloc( sizeof(int) *3 );
                 ans[*returnSize][0] = nums[begin]; 
                 ans[*returnSize][1] = nums[l];
                 ans[*returnSize][2] = nums[r];
                 (*returnSize) ++;
                 while ( ++l < r && nums[l] == nums[l-1] )  ;
                 r--;               
            }
        }        	 
    }
   return ans;
}
void Adjust_heap(int *nums ,int parent,int len){
    
    int child = 2*parent +1 ;  //Find left child   
    int temp =  nums[parent];   //store  parent to temp
    
    while(child<len){
        if(  child+1 < len && nums[child] < nums[child+1])  //if right child exit and right child bigger than left , use right child
        {
            child += 1 ;  //get right child            
        } 
        /* parent node bigger than the child ， this node is ok。 but when exchange a small number to parent ，need to look down until the             child node is bigger than temp（which is the intial parent）*/  
        if ( temp >= nums[child])  
            break ;
        nums[parent] = nums[child] ;
        parent =  child ;
        child = 2*parent + 1;
    }
    nums[parent] = temp ;
}

void sort_use_heap (int *nums ,int numsSize){
    int temp ;
    for ( int i = numsSize/2 ; i >= 0; i--) //creat and adjust node
        Adjust_heap(nums,i,numsSize);    
    /* after adjust every node of heap, a big root heap is created */
    /* now we sort the array ,every time we change nums[0] and nums[end] , re_arrange the heap ,then putput the nums[end] */
    for(int i = numsSize-1 ;i>0; i--){ 
        /*exchange nums[0] with nums[end] */
        temp = nums[0];
        nums[0] = nums[i];
        nums[i] = temp ;
        /* re_arrange ,let the biggest nubmer go to nums[0] */
        Adjust_heap(nums,0,i);           
    }    
}
