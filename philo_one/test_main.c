#include "philo.h"

void *try_func(int *arr, int start, int end)
{
	pthread_mutex_lock();
	int i = 0;

	while (start < end)
	{
		arr[i] += 1;
		i++;
	}
}

int main(void)
{
	// for (int i = 0; i < 1000; i++)
	int i = 0;
	t_time tm;
	t_time tm2;
	size_t all1, all2;
	int *arr[1000];

	while (i < 1000)
	{

	}
	gettimeofday(&tm, NULL);
	printf("sec = %ld\n", tm.tv_sec);
	printf("sec = %ld\n", (all1 = tm.tv_sec * 1000));
	printf("usec = %ld\n", tm.tv_usec);
	printf("usec = %ld\n", (all2 = tm.tv_usec / 1000));
	printf("all = %ld\n", all1 + all2);
	while (i < 110000)
		i++;
	gettimeofday(&tm, NULL);
	printf("2sec = %ld\n", tm.tv_sec);
	printf("2sec = %ld\n", (all1 = tm.tv_sec * 1000));
	printf("2usec = %ld\n", tm.tv_usec);
	printf("2usec = %ld\n", (all2 = tm.tv_usec / 1000));
	printf("2all = %ld\n", all1 + all2);
	return (0);
}
