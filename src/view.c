#include "controller.h"

int index_view(void* p, onion_request* req, onion_response* res){

	char* buffer = MakeTemplateBuffer(NULL, "test_template/index.html");
	if(buffer == NULL){
		ONION_INFO("open_memstream() return NULL");
		return OCS_INTERNAL_ERROR;
	}
	onion_response_printf(res, "%s", buffer);
	free(buffer);
	return OCS_PROCESSED; 
}


char* MakeTemplateBuffer(TMPL_varlist* context, const char* template_path){
	char* buffer; 
	size_t size; 
	FILE* out = open_memstream(&buffer, &size); 
	if(out == NULL){
		return NULL; 
	}

	TMPL_write(template_path, 0, 0, context, out, stderr);
	fclose(out); 
	return buffer;
}

char* read_file(const char* filename){
	int fd = open(filename, O_RDONLY);
	if(fd < 0) return NULL; 

	unsigned int file_size = lseek(fd, 0, SEEK_END); 
	char* buffer = (char*)malloc(sizeof(char) * (file_size + 1)); 
    lseek(fd, 0, SEEK_SET);
	unsigned int total = 0; 
	do{
		total += read(fd, buffer+total, file_size);
	}while(total < file_size); 

	buffer[total] = '\0'; 
	close(fd); 
	return buffer;
}
