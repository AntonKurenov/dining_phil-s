#include "philo.h"

int arr[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *print_num(void *arg)
{
	int index = *(int*)arg;
	if (index % 2 == 0)
	{
		sleep(1);
		printf("%% \n");
	}
	// printf("  |index = %d =", index);
	printf("%d ||", arr[index]);
	free(arg);
}

int main(int argc, char **argv)
{
	int i = 0;
	pthread_t th[10];
	int *index_arr;
	int *tmp;

	if (!(index_arr = (int *)malloc(sizeof(int) * 10)))
		return (9);
	while (i < 10)
	{
		tmp = malloc(sizeof(int));
		*tmp = i;
		// printf("tmp = %d\n", i);
		if (pthread_create(th + i, NULL, &print_num, tmp) != 0)
		{
			perror("cannot create thread");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("failed to join thread");
			return (2);
		}
		i++;
	}
	printf("\n");
}
