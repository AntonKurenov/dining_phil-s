#include "philo.h"

int g = 0;
pthread_mutex_t mutex;

void *increment() 
{
	pthread_mutex_lock(&mutex);
	for (int i = 0; i < 10000000; i++)
	{
		g++;
	}
	pthread_mutex_unlock(&mutex);
} 

int main() 
{ 
	// pthread_t th[10];
    // pthread_t thread_1, thread_2;
	// pthread_t t1, t2;
	pthread_mutex_init(&mutex, NULL);
	int i = 0;
	size_t t_start, time_end;

	t_start = ft_gettime();
	printf("n 0 \n");
	ft_sleep(2000);
	// while (i < 4)
	// {
	// 	if (pthread_create(th + i, NULL, &increment, NULL) != 0)
	// 	{
	// 		perror("Failed to create thread");
	// 		return (1);
	// 	}
	// 	if (pthread_join(th[i], NULL) != 0)
	// 		return (2);
	// 	i++;
	// }
	// i = 0;
	// // while (i < 4)
	// // {
	// // 	if (pthread_join(th[i], NULL) != 0)
	// // 		return (2);
	// // 	i++;
	// // }
	// printf("Before Thread\n"); 
	// pthread_mutex_destroy(&mutex);
	// printf("after: g = %d\n", g);
	time_end = ft_gettime();
	// printf("time = %ld\n", time_end - t_start);
	// printf("num = %d\n", 1 % 2);
	// printf("num2 = %d\n", 0 % 2);
	printf("end\n");
    exit(0); 
}
