


static void parse_preference(char* buffer, int length){

	int arch32hash = _dictionary_hash("arch32");
	int arch64hash = _dictionary_hash("arch64");

	if(_dictionary_hash(buffer) == arch32hash)
		printf("Set 32 bit architecture...\n");

	if(_dictionary_hash(buffer) == arch64hash)
		printf("Set 64 bit architecture...\n");


	return;

}

static void parse_global_process_buffer(char* buffer, int length){

	//printf("%s \n", buffer);

	if(buffer[0] == '.')
		parse_preference(buffer + 1, length - 1);

	return;

}

void _parse_global_line(fline* ln){

	int i = 0;
	int j = 0;

	char buffer[30];

	while(ln->line[i] && ln->line[i] != '#'){

		if(ln->line[i] != ' ')
			buffer[j++] = ln->line[i];

		else{

			parse_global_process_buffer(buffer, j);
			memset(buffer, 0, 30);
			j = 0;

		}

		i++;

	}

	parse_global_process_buffer(buffer, j);

	return;
	

}