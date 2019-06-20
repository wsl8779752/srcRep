#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int key;
    int val;
}Hash_node;

typedef struct{
    int size;
    Hash_node **pointer;
}Hash_map;

Hash_map* Hash_map_creat(int Size)
{
    Hash_map *my_hashmap ;
    my_hashmap = malloc( sizeof(Hash_map ));
    my_hashmap->size = Size;
    my_hashmap->pointer = calloc(Size,sizeof(Hash_node *));
    return my_hashmap  ;
}

Hash_node * Hash_get(Hash_map * hash_map ,int num)
{
    int key = abs(num)% hash_map->size;
    Hash_node * hash_node;
    while( ( hash_node = hash_map->pointer[key]))
    {
        if(hash_node->key ==num)
            return hash_node ;
        if( key< hash_map->size-1)
            key++;
        else key=0;
    }
    return 0;
}

void Hash_set(Hash_map * hash_map,int num ,int i)
{
    int key = abs(num)% hash_map->size;
    Hash_node * hash_node;
    while( (hash_node = hash_map->pointer[key]) )
    {
        if( key< hash_map->size-1)
            key++;
        else key=0;
    }
    hash_node = malloc( sizeof( Hash_node) );
    hash_map->pointer[key] = hash_node;
    hash_node->key = num;
    hash_node->val = i;
}

void  Hash_destroy( Hash_map *hash_map ,int *nums ,int i)
{
     Hash_node * hash_node;
     int key,index;
     for( index=0;index<i;index++)
     {
         key = abs(nums)% hash_map->size;
         while( (hash_node = hash_map->pointer[key]) )
             free(hash_node) ;
     }
     free(hash_map->pointer);
     free(hash_map->pointer);


}
int* twoSum(int* nums, int numsSize, int target) {
    int i;
    Hash_map *main_hash_map ;
    main_hash_map = Hash_map_creat(numsSize*2);
    int result[2];
    for(i=0;i<numsSize;i++)
    {
        int rest= target-nums[i];
        Hash_node *node = Hash_get( main_hash_map,rest) ;
        if(node){
            result[0] = i;
            result[1] = node->val;
        //    Hash_destroy(main_hash_map ,nums , i);
            return result;
        }
        else {
            Hash_set( main_hash_map,nums[i],i);
        }
    }
    return 0;
}
int main()
{
    int nums[3] = {3, 2 ,4} ;
    int target =6 ;
    int *d = twoSum(nums,3,6) ;
    printf("%d %d",*d++,*d);
    return 0;
}
