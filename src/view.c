#include "controller.h"

int index_view(void* p, onion_request* req, onion_response* res){

	TMPL_varlist* context = NULL;
	TMPL_varlist* portfolio_list_var = NULL; 
	TMPL_varlist* portfolio_detail_var = NULL;
	TMPL_varlist* portfolio_title = NULL;

	TMPL_loop* loop = NULL; 

	char number[30] = {0, };
    char* title_list[3] = {"test1 1등", "test대회 2등", "test대회 3등"};	

	for(int i=0;i<3;i++){
		sprintf(number, "%s%d", "portfolio", i); 
		portfolio_list_var = TMPL_add_var(0, "portfolio_id", number, "main_portfolio_title",title_list[i], 0);
	    loop = TMPL_add_varlist(loop, portfolio_list_var); 	
	}

	context = TMPL_add_loop(context, "portfolio_list", loop);
	
	loop = NULL; 
	for(int i=0;i<3;i++){
		sprintf(number, "%s%d", "portfolio", i);
		portfolio_detail_var = TMPL_add_var(0, "portfolio_id", number, "portfolio_title", title_list[i], 0); 
		//portfolio_title = TMPL_add_var(0, "portfolio_title", title_list[i], 0); 
		loop = TMPL_add_varlist(loop, portfolio_detail_var); 
	}

	context = TMPL_add_loop(context, "portfolio_detail", loop); 

	char* buffer = MakeTemplateBuffer(context, "template/index.html");
	if(buffer == NULL){
		ONION_INFO("open_memstream() return NULL");
		return OCS_INTERNAL_ERROR;
	}
	onion_response_printf(res, "%s", buffer);
	free(buffer);
	TMPL_free_varlist(context);
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
