#include <onion/onion.h>
#include <onion/log.h>
#include <signal.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

#include "ctemplate.h"
#include <string.h>
#include "exportlocal.h"
//#include <onion/handlers/exportlocal.h>
#include "cJSON.h"

typedef struct _DirList{
	char* filename; 
	char* title; 
	char* buffer;
   	char* id; 	
	struct _DirList* next; 
}DirList; 

typedef struct _DirHead{
	DirList* head; 
	DirList* tail;
}DirHead;

void shutdown_server(int _); 
onion_url* init_url(); 

int index_view(void* p, onion_request* req, onion_response* res); 
TMPL_varlist* index_template(); 

char* MakeTemplateBuffer(TMPL_varlist* context, const char* template_path);
char* read_file(const char* filename);


DirHead* dirhead_new();
void Insert_dir(DirHead* dirhead, char* filename, char* title, char* id); 
void Delete_dir(DirHead* dirhead); 


char* parse(char* filename);









