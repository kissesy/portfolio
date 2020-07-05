#include "controller.h"

void do_log(char* msg){
	time_t t = time(NULL); 
	struct tm tm = *localtime(&t); 

	char* time_string = (char*)malloc(40); 
	sprintf(time_string, "[%d-%d-%d %d:%d:%d]", tm.tm_year+1900, 
												tm.tm_mon+1,
												tm.tm_mday,
												tm.tm_hour, 
												tm.tm_min,
												tm.tm_sec);

	
	ONION_INFO("%s %s",time_string, msg);
	free(time_string);
}
