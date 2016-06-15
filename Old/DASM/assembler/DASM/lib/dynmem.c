

//Structure for keeping track of memory allocations through malloc.
struct dasm_alloc{

	void* ptr;
	struct dasm_alloc* prev;
	struct dasm_alloc* next;

};

typedef struct dasm_alloc dasm_alloc;

//Allocation pool.
dasm_alloc* gc_pool = 0;

void* dasm_malloc(unsigned int sz){

	void* nptr;
	dasm_alloc* rk;

	nptr = malloc(sz);

	if(nptr){

		rk = (dasm_alloc*)malloc(sizeof(dasm_alloc));
		rk->ptr = nptr;
		rk->prev = rk;
		rk->next = 0;

		if(!gc_pool)
			gc_pool = rk;

		else{

			rk->prev = gc_pool->prev;
			rk->next = gc_pool;
			gc_pool->prev->next = rk;
			gc_pool->prev = rk;

		}

	}

	return nptr;

}

void dasm_free(void* ptr){

	dasm_alloc* tmp;

}

void  dasm_mfree(){

	dasm_alloc* tmp;
	unsigned short total = 0;

	while(tmp != gc_pool){

		tmp = gc_pool->prev;
		tmp->prev->next = gc_pool;
		gc_pool->prev = tmp->prev;

		free(tmp->ptr);
		free(tmp);
		total++;

	}

	gc_pool = 0;

	printf("\nFreed a total of: %d allocations!\n", total);


}