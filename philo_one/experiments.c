#include "philo.h"

int g = 0;

void *myThreadFun(void *vargp) 
{ 
    sleep(2); 
	g++;
    printf("Printing GeeksQuiz from Thread \n"); 
    return NULL; 
} 

int main() 
{ 
    pthread_t thread_1, thread_2;
    printf("Before Thread\n"); 
    pthread_create(&thread_1, NULL, myThreadFun, NULL); 
    sleep(1); 
    pthread_create(&thread_2, NULL, myThreadFun, NULL); 
    pthread_join(thread_1, NULL); 
    pthread_join(thread_2, NULL); 
    printf("After Thread\n"); 
    exit(0); 
}
