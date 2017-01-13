#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>
 
pthread_mutex_t mut_motocell;

pthread_t ptrecvdispatch;
pthread_t ptdomotocell;
pthread_t ptwhomai;

unsigned long long int cnt;

void thread_handler_close(void) {
    pthread_cancel(ptrecvdispatch);
    pthread_cancel(ptdomotocell);
    pthread_cancel(ptwhomai);
}

void ptwhomai_main(void) {

    pthread_detach(pthread_self());

	  while(1){
          cnt++;
          if((cnt%100000000) == 0)
		    printf("[Debug] cnt = %lld\n", cnt);		  		  
	  }
	  return;
}

void ptrecvdispatch_main(void) {

    pthread_detach(pthread_self());

	  while(1){
		  pthread_mutex_lock(&mut_motocell);
            sleep(5);
		  pthread_mutex_unlock(&mut_motocell);
		  usleep(1000);
	  }
	  return;
}

void ptmotoldcell_main(void) {

    pthread_detach(pthread_self());

	  while(1){
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

    printf("creating do ptwhomai action thread\n");
    status = pthread_create(&ptwhomai, NULL, (void*)&ptwhomai_main, NULL);
    if (status != 0) {
        printf("Failed to create ptwhomai thread with status = %d\n", status);
    }
    sleep(10);
    //while(1);
 	  thread_handler_close();
    return (0);
}
