//program simulasi untuk soal OS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

sem_t synch1, synch2;

clock_t t;

void init(){
	srand(time(NULL));
	t=clock();
	sem_init(&synch1,0,0);
	sem_init(&synch2,0,0);
}

void randomWait(const char * tname){
	printf("%s started. time = %f \n", tname, ((double) (clock()-t))/CLOCKS_PER_SEC);
	usleep(rand()%2000000);
	printf("%s finished. time = %f \n", tname, ((double) (clock()-t))/CLOCKS_PER_SEC);
}

//ini bagian threadnya

void* T1(void * arg){
	randomWait("S1");
	sem_post(&synch1); //post: signal
	sem_post(&synch1);
	pthread_exit(0);
}

void* T2(void * arg){
	sem_wait(&synch1);
	randomWait("S2");
	sem_post(&synch2);
	pthread_exit(0);
}

void* T3(void * arg){
	sem_wait(&synch1);
	randomWait("S3");
	sem_post(&synch2);
	pthread_exit(0);
}

void* T4(void * arg){
	sem_wait(&synch2);
	sem_wait(&synch2);
	randomWait("S4");
	pthread_exit(0);
}



int main(){
	pthread_t t1,t2,t3,t4;
	pthread_create(&t1, NULL, T1, NULL);
	pthread_create(&t2, NULL, T2, NULL);
	pthread_create(&t3, NULL, T3, NULL);
	pthread_create(&t4, NULL, T4, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);

	return 0;
}
