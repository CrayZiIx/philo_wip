#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h> 

typedef struct s_mutex_fork{
	int locked;
	pthread_mutex_t mutex;
}		t_mutex_fork;

typedef struct s_mutex_glob{
	t_mutex_fork	data;
	pthread_mutex_t mutex;
}		t_mutex_glob;

void *routine(void *arg)
{
	// t_mutex_glob	*glob = (t_mutex_glob *)arg;
	pthread_mutex_t	*mutex = (pthread_mutex_t *)arg;
	pthread_t tid;
	tid = pthread_self();
	// while (1)
	// {
	// pthread_mutex_lock(&glob->mutex);
	// pthread_mutex_lock(mutex);
	if (mutex->__data.__lock == 0)
	{
		// printf("unlock\n");
		pthread_mutex_lock(mutex);
		printf("%ld EAT\n",tid);
		pthread_mutex_unlock(mutex);
	}	
	else
	{
		printf("lock\n");
		pthread_mutex_lock(mutex);
		printf("unlock now\n");
	}	
	// pthread_mutex_unlock(&glob->mutex);
	// }
	// printf("state = %d\n", glob->data.mutex.__data.__lock);
	// printf("state = %d\n", glob->data.mutex.__data.__lock);
	return (NULL);
}

philo(cycle) has a thread(death)


void *death(void *arg)
{
	while(isr == TRUE)
	{
		if (get_time - last_meal(timer) > die_time)
		{
			isr = FALSE; // no one can printf
			printf("philo[x] is dead\n");
		}
	}
}

int main(void)
{
	// t_mutex_glob	*glob0;
	// t_mutex_glob	*glob1;
	pthread_mutex_t		*mutex;

	mutex = malloc(nb philo);

	philo{
		left ->> mutex[left];
		right = left + 1 sauf si left = nb philo alors right = 0->> mutex[right];
	}
	pthread_t thread1;
	pthread_t thread2;

	// glob0 = malloc(sizeof(t_mutex_glob));
	// glob1 = malloc(sizeof(t_mutex_glob));
	// pthread_create(&thread1, NULL, routine, &glob0->data.mutex);
	// pthread_create(&thread2, NULL, routine, &glob0->data.mutex);
	// pthread_create(&thread, NULL, routine, &glob1->data.mutex);

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread1, NULL, routine, &mutex);
	usleep(50);
	pthread_create(&thread2, NULL, routine, &mutex);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return (0);


}





