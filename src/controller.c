#include "controller.h"

onion* server = NULL; 

int main(int argc, char** argv){
	signal(SIGINT, shutdown_server); 
	signal(SIGTERM, shutdown_server); 

	server = onion_new(O_POLL); 
	onion_url* urls = init_url(); 

	do_log("Start Server");
	onion_listen(server); 
	onion_free(server); 
	return 0;
}

void shutdown_server(int _){
	if(server){
		onion_listen_stop(server);
	   //onion_free(server);	
	}
}

onion_url* init_url(){
	onion_set_hostname(server, "0.0.0.0"); 
	onion_url* urls = onion_root_url(server); 

	onion_url_add(urls, "", index_view); 
	onion_url_add_handler(urls,"^assets", onion_handler_export_local_new("template/assets"));
	onion_url_add_handler(urls,"^js", onion_handler_export_local_new("template/js"));
	onion_url_add_handler(urls,"^css", onion_handler_export_local_new("template/css"));
	return urls; 
}
