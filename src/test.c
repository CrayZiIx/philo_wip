#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> // thread mutex
#include <sys/time.h> // gettimeoftheday

#define THREAD_COUNT 4

typedef struct mutex_data {
	int				data[THREAD_COUNT]; // this gonna be int *data = malloc(sizeof(ft_atoi(av[1]));
	int				id;
	pthread_mutex_t	mutex;
	int is_dead;
} mutex_data;

// int *data;

// data = malloc(sizeof(int) * THREAD_COUNT);

// int data[THREAD_COUNT];

void	*routine(void *arg)
{
	int	id;
	mutex_data *md;
	pthread_t tid;
	
	md = (mutex_data *) arg;
	tid = pthread_self();
	(void)tid;
	pthread_mutex_lock(&(*md).mutex);
	id = md->id;
	md->id++;
	pthread_mutex_unlock(&(*md).mutex);
	md->data[id] = id % 2;
	while (md->data[id] < 10)
	{
		pthread_mutex_lock(&(*md).mutex);
		if ((*md).data[id] % 2 == 0)
		{
			printf("thread [ %d ] is going to eat\n", id);
			// fflush(stdout);
		}
		else
		{
			printf("thread [ %d ] is going to sleep\n", id);
			// fflush(stdout);
		}
		(*md).data[id] = (*md).data[id] + 1;
		pthread_mutex_unlock(&(*md).mutex);
		if (id == 3)
			printf("----------------\n");
		// fflush(stdout);
		usleep(100); // sale
	}
	return (NULL);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	pthread_t *philo;
	static mutex_data md = {0};
	int i = 0;
	philo = malloc(sizeof(pthread_t) * THREAD_COUNT);
	pthread_mutex_init(&md.mutex, NULL);
	while (i < THREAD_COUNT)
		pthread_create(&philo[i++], NULL, routine, &md);
	i = 0;
	while (i < THREAD_COUNT)
		pthread_join(philo[i++], NULL);
	pthread_mutex_destroy(&md.mutex);
	return (0);
}
