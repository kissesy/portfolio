#include "controller.h"


//dirlist 를 가리키기위한 head, tail 구조체 
DirHead* dirhead_new(){
	DirHead* dirhead = (DirHead*)malloc(sizeof(DirHead)); 
	if(dirhead == NULL){
		do_log("malloc() in dirhead_new() return NULL");
		return NULL; 
	}
	dirhead->head = NULL; 
	dirhead->tail = NULL; 
	return dirhead; 
}

void Insert_dir(DirHead* dirhead, char* filename, char* title, char* id){
	
	DirList* newdir = (DirList*)malloc(sizeof(DirList));
	newdir->filename = (char*)malloc(strlen(filename) + 1); 

	strcpy(newdir->filename, filename); 
	//newdir->buffer = parse(newdir->filename);
	newdir->buffer = read_file(newdir->filename); 

	//newdir->title = title; 이렇게 하면 나중에 free문제가 생김 추천방법은 인자로 받은것은 그대로 쓰지 않고 할당해서 따로 만들면 편함 
	newdir->title = (char*)malloc(strlen(title) + 1); 
	strcpy(newdir->title, title); 
	
	newdir->id = (char*)malloc(strlen(id) + 1); 
	strcpy(newdir->id, id); 
	
	newdir->next = NULL; 

	if(dirhead->head == NULL){
		dirhead->head = newdir; 
		dirhead->tail = newdir; 
	} else {

		dirhead->tail->next = newdir; 
		dirhead->tail = newdir; 
	}
}

//dirhead도 free need 
void Delete_dir(DirHead* dirhead){
	DirList* curr = dirhead->head; 
	DirList* prev = curr; 
	while(curr != NULL){
		//printf("deleted!\n");
		prev = curr;
	    curr = curr->next; 	
		free(prev->filename);
	    free(prev->buffer);
		free(prev->id);
		free(prev->title);
		free(prev); 
	}	
}





















