void Adjust_heap(int *nums ,int parent,int len);
void sort_use_heap (int *nums ,int numsSize);

int threeSumClosest(int* nums, int numsSize, int target) {
    int begin , l ,r ,temp ,ans ;
    if ( numsSize < 3) return 0;    
    sort_use_heap(nums,numsSize);// sort array in increasing  order
    
    /*if the smallest number in array is smaller than target , we find the nearest 3sum which is nums[0] + nums[1] +nums[2]*/       if ( nums[0] >= 0 && target <= 0 ) return (nums[0] + nums[1] +nums[2]); 
    
    /* the same idea as smallest number in array ,but this time is the biggest one in array */
    if( nums[numsSize -1] <= 0 && target >= 0)  return nums[numsSize -3] +nums[numsSize -2]+nums[numsSize -1];
    
    for(ans = nums[0] + nums[1] + nums[2], begin = 0 ; begin < numsSize -2 ;begin ++){
        /*if the smallest 3sum under a given "begin" is bigger than target, the cloest 3sum in this circulation finded  */
        if (  (temp = nums[begin] + nums[begin+1] + nums[begin+2] ) > target   ) { 
            ans = temp-target < abs(ans-target) ? temp : ans ;
            continue ;
        } 
        /*if the biggest 3sum under a given "begin" is smaller than target, the cloest 3sum in this circulation finded  */
        if(  (temp = nums[begin] + nums[numsSize-2] + nums[numsSize-1] ) < target  ){
            ans = abs(temp - target) < abs(ans-target) ? temp : ans  ; 
            continue;
        }           
        l =  begin+ 1, r = numsSize - 1;
        while ( l < r ){
            if( (temp = nums[begin] + nums[l] +nums[r] ) < target ){
                ans = abs( temp - target) < abs( ans - target) ? temp : ans;
                while (++l < r && nums[l]== nums[l-1] ); //jump over repeated nums[l]
            }                
            else if ( temp > target){
                ans = temp-target < abs(ans-target) ? temp : ans;
                while( l< --r && nums[r] == nums[r+1]);//jump over repeated nums[r]
            }             
            else return temp;
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
