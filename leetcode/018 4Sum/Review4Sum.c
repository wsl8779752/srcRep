#include <string.h>/**
 *  * Return an array of arrays of size *returnSize.
 *   * Note: The returned array must be malloced, assume caller calls free().
 *    */
void Apjust_heap(int *nums ,int parent,int len);
void sort_use_heap (int *nums ,int numsSize);

int** fourSum(int* nums, int numsSize, int target, int* returnSize) {
	int begin,second,left,right,rest,sum;

	if ( numsSize  < 4) return NULL;
	int **ans_array = malloc( sizeof(int *)); //char *错误
	sort_use_heap (nums , numsSize);
	for(  *returnSize = 0,begin  = 0 ;begin < numsSize -3 ; begin++){
		if( begin!=0 && nums[begin]== nums[begin-1]) continue;
		for( second = begin+1;second < numsSize -2 ;second ++){
			if( second != begin+1 && nums[second] == nums[second-1]) continue;
			rest = target - nums[begin] - nums[second];
			if( nums[second+1]+nums[second+2] > rest)  break; //更换begin second
			if( nums[numsSize-2] + nums[numsSize-1]  < rest )      continue; //增大second
			left = second +1;
			right = numsSize -1 ;
			while (left < right){
				sum =  nums[left] + nums[right];
				if( sum < rest)   left++;
				else if (sum > rest) right--;
				else{
					//realloc a size of *returnSize memory for ans_array( type array of pointer's pointer)
					if(*returnSize ){
						ans_array = realloc(ans_array,(*returnSize+1)*sizeof(int *)); //here mistake
					}
					ans_array[*returnSize] = malloc(4*sizeof(int));// piece of memory for the finded elements 
					//copy finded elements to the  allocated piece of memory
					ans_array[*returnSize][0] = nums[begin];
					ans_array[*returnSize][1] = nums[second];
					ans_array[*returnSize][2] = nums[left];
					ans_array[*returnSize][3] = nums[right];
					while ( ++left < right && nums[left] == nums[left-1]);
					while( left < --right && nums[right] == nums[right+1]);
					*returnSize+=1;
				}
			}
		}
	}
	return ans_array ;
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