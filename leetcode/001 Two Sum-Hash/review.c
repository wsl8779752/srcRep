typedef struct hashnode{
	int array_num ;
	int array_index;
}HASH_NODE;

typedef struct hashmap{
	int size;
	HASH_NODE **table;
}HASH_MAP;

void hash_map_create(int numsSize,HASH_MAP *hashmap)
{
	hashmap->size =numsSize;
	hashmap->table = calloc( numsSize , sizeof(HASH_NODE *) );
}
void  hash_destroy( HASH_MAP *hashmap )
{
	HASH_NODE * node;
	int i;
	for(i=0;i<hashmap->size;i++)
	{
		if((node = hashmap->table[i])) {
			free(node);
		}
	}
	free(hashmap->table);
}


void hash_set(int num ,int i ,HASH_MAP * hashmap)
{
	int hash = abs(num) % hashmap->size;
	HASH_NODE * node;
	while( (node = hashmap->table[hash]) )
	{
		if( hash < hashmap->size-1)
			hash++;
		else hash= 0;
	}
	node = malloc( sizeof( HASH_NODE) );
	hashmap->table[hash] = node;
	node->array_num = num;
	node->array_index = i;
}

int  hash_get(int num, HASH_MAP * hashmap )
{
	int hash = abs(num)% hashmap->size;
	HASH_NODE * node;
	while( ( node = hashmap->table[hash]))
	{
		if(node->array_num == num)
			return node->array_index;
		if( hash< hashmap->size-1)
			hash++;
		else hash=0;
	}
	return -1;
}

int* twoSum(int* nums, int numsSize, int target) {
	HASH_MAP main_hashmap ;
	int i,j,rest;
	hash_map_create(numsSize*2,&main_hashmap );
	for(i=0;i<numsSize;i++)
	{
		rest= target-nums[i];
		j = hash_get(rest, &main_hashmap) ;
		if(j!= -1){
			int *result = malloc(sizeof(int)*2) ;
			result[0] = j ;
			result[1] = i ;
			hash_destroy(&main_hashmap );
			return result;
		}
		else {
			hash_set( nums[i],i, &main_hashmap);
		}
	}
	return NULL;
}

