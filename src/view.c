#include "controller.h"

TMPL_varlist* index_template(){
	TMPL_varlist* context = NULL;
	TMPL_varlist* portfolio_list_var = NULL; 
	TMPL_varlist* portfolio_detail_var = NULL; 

	TMPL_loop* portfolio_list_loop = NULL; 
	TMPL_loop* portfolio_detail_loop = NULL; 

	DirHead* dirhead = dirhead_new(); 
	if(dirhead == NULL){
		return NULL; 
	}
	
	//json 파싱
	char* buffer = read_file("json/list.json");
	if(buffer == NULL){
		free(dirhead); 
		do_log("read_file return NULL");
		return NULL;
	}
	const cJSON* dirlist = NULL; 
    const cJSON* dir = NULL; 
	//json parse error 
	cJSON* monitor = cJSON_Parse(buffer);
	if(monitor == NULL){
		free(dirhead); 
		return NULL; 	
	}
	//dirlist 구조체 형태로 filepath, title, content 담음 need free buffer, filename, title, id 
	dirlist = cJSON_GetObjectItemCaseSensitive(monitor, "dirlist"); 
	if(dirlist == NULL){
		do_log("cJSON_GetObjectItemCaseSensitive() return NULL");
		free(dirhead); 
		free(buffer); 
		cJSON_Delete(monitor); 
		return NULL; 
	}
	cJSON_ArrayForEach(dir, dirlist){
		
		cJSON* title = cJSON_GetObjectItemCaseSensitive(dir, "title"); 
		cJSON* filepath = cJSON_GetObjectItemCaseSensitive(dir, "filepath");
	    cJSON* id = cJSON_GetObjectItemCaseSensitive(dir, "id");
	
		//json값이 정상적으로 파싱이 된다면	
		if((filepath->valuestring != NULL) && (title->valuestring != NULL) && (id->valuestring != NULL)){	
			Insert_dir(dirhead, filepath->valuestring, title->valuestring, id->valuestring);
		}
	}

	//template에 넣기위한 context 작업 
	DirList* curr = dirhead->head;
	while(curr != NULL){

		//list는 프로젝트들 나열 아래 TMPL_add_var같은 함수들은 인자로 들어오는 문자열 포인터들을 그대로 쓰지 않고 동적할당하고 씀 그럼 나중에 free걱정이 덞. 
		portfolio_list_var = TMPL_add_var(0, "portfolio_id", curr->id, 
											 "main_portfolio_title", curr->title, 0);

		//detail은 프로젝트 세부 내역들 클릭시 dialog가 뜨고 내부 글은 buffer 넣을건데 이건 잠시 기달 buffer의 내용은 markdown 
		portfolio_detail_var = TMPL_add_var(0, "portfolio_id", curr->id, 
											   "portfolio_title", curr->title, 
											   "content", curr->buffer, 0); //buffer은 나중에 

		portfolio_list_loop = TMPL_add_varlist(portfolio_list_loop, portfolio_list_var); 
		portfolio_detail_loop = TMPL_add_varlist(portfolio_detail_loop, portfolio_detail_var); 
		curr = curr->next; 
	}

	context = TMPL_add_loop(context, "portfolio_list", portfolio_list_loop);
	context = TMPL_add_loop(context, "portfolio_detail", portfolio_detail_loop); 	
	
	free(buffer);
	cJSON_Delete(monitor);
	Delete_dir(dirhead);
	free(dirhead);
	return context; 
}


int index_view(void* p, onion_request* req, onion_response* res){

	ONION_INFO("%s %s","client connect!",onion_request_get_client_description(req));
	do_log("request index view!");
	TMPL_varlist* context = index_template(); 
	if(context == NULL){
		do_log("index template() return NULL");
		return OCS_INTERNAL_ERROR;
	}
	char* buffer = MakeTemplateBuffer(context, "template/index.html");
	if(buffer == NULL){
		do_log("open_memstream() return NULL");
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
