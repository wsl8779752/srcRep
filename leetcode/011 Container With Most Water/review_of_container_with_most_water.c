int maxArea(int* height, int heightSize) {
    int i,j,area,max_area,min_num,width;
    max_area = 0;        
    i=0 ;
    j = heightSize-1 ; 
    while( i < j){
        width = j -i ;
        if(  height[i] < height[j]){
            min_num =  height[i];
            while( ++i < j && height[i]<= min_num );
        }            
        else {  
            min_num = height[j];
            while( i < --j && height[j]<= min_num );
        }       
        area =  min_num *width ;
        max_area = max_area > area ? max_area : area ;        
    }
    return max_area ;
}
