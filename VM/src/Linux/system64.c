
typedef unsigned long vpu_vector;


//Generates a new vpu vector. Returns a pointer to the vector on success, 0 on failure.
vpu_vector* _sys_create_vpu_vector(){

	vpu_vector* b64v;

	b64v = (vpu_vector*)malloc(2384);

	return b64v;

}

void _sys_destroy_vector(vpu_vector* b64v){

	if(b64v)
		free(b64v);

}

//Auto create a new pool of memory. Returns a pointer to the memory pool upon success, 0 on failure.
void* _sys_auto_memory_setup(vpu_vector* b64v, unsigned long sz){

	void* mpool;

	mpool = malloc(sz);

	if(mpool && b64v){

		b64v[255] = (unsigned long)mpool;
		b64v[256] = sz;

	}

	return mpool;

}

//Connect a previously created pool of memory.
void _sys_memory_connect(vpu_vector* b64v, void* mem, unsigned long sz){

	if(b64v && mem){

		b64v[255] = (unsigned long)mem;
		b64v[256] = sz;

	}
}

//Manually free system memory.
void _sys_memory_disconnect(vpu_vector* b64v){

	if(b64v)
		free((void*)b64v[255]);

	return;
}



