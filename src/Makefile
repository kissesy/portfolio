
LDFLAGS=-lpthread -lonion_static -lrt


webserver : controller.o cJSON.o exportlocal.o view.o ctemplate.o dir.o
	gcc -o webserver controller.o cJSON.o exportlocal.o view.o ctemplate.o dir.o -lpthread -lonion_static -lrt 

dir.o : controller.h dir.c 
	gcc -c -o dir.o dir.c

controller.o : controller.h controller.c 
	gcc -c -o controller.o controller.c 

cJSON.o : cJSON.h cJSON.c 
	gcc -c -o cJSON.o cJSON.c 

exportlocal.o : exportlocal.h exportlocal.c 
	gcc -c -o exportlocal.o exportlocal.c 

view.o : controller.h view.c 
	gcc -c -o view.o view.c

ctemplate.o : ctemplate.h ctemplate.c 
	gcc -c -o ctemplate.o ctemplate.c 

clean: 
	rm *.o webserver 


