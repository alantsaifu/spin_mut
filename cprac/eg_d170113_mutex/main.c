#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>
 
pthread_mutex_t mut_motocell;
pthread_t ptrecvdispatch;
pthread_t ptdomotocell;

void thread_handler_close(void) {
    pthread_cancel(ptrecvdispatch);
    pthread_cancel(ptdomotocell);
}

void ptrecvdispatch_main(void) {

    pthread_detach(pthread_self());

	while(1){
		printf("[Debug] I am the ptrecvdispatch_main\n");
		//pthread_mutex_lock(&mut_motocell);
		//pthread_mutex_unlock(&mut_motocell);
		usleep(1000);
	}
	return;
}

void ptmotoldcell_main(void) {

    pthread_detach(pthread_self());

	while(1){
		//printf("[Debug] I am the ptmotoldcell_main\n");
		pthread_mutex_lock(&mut_motocell);
		sleep(10);
		pthread_mutex_unlock(&mut_motocell);
		usleep(1000);
	}
	return;
}

int main(int argc, char *argv[])
{
	int status;
	
    pthread_mutex_init(&mut_motocell,NULL);

    printf("creating the recv command and dispatched pthread\n");
	status = pthread_create(&ptrecvdispatch, NULL, (void*)&ptrecvdispatch_main, NULL);
    if (status != 0) {
        printf("Failed to create ptrecvdispatch with status = %d\n", status);
    }    

    printf("creating do motocell action thread\n");
    status = pthread_create(&ptdomotocell, NULL, (void*)&ptmotoldcell_main, NULL);
    if (status != 0) {
        printf("Failed to create ptdomotocell thread with status = %d\n", status);
    }

    while(1);
 	thread_handler_close();
    return (0);
}
