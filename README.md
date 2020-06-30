
hello

install 

1. lictemplate 
2. libonion 
3. cJSON 

problem 

1. onion/handler/exportlocal.h don't compile. So, i move exportlocal.c and exportlocal.h in src folder

compile : gcc view.c controller.c ctemplate.c exportlocal.c -lonion_static -lpthread -lrt
