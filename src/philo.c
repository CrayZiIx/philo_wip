/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:26:48 by jolecomt          #+#    #+#             */
/*   Updated: 2023/12/22 15:39:24 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool check_if_dead(t_philo *philo, long int current_time)
{
	pthread_mutex_lock(&philo->global->mutex_global);
	if(philo->global->is_running == TRUE)
	{
		if (current_time - philo->time_since_last_meal >= philo->global->tmd)
		{
			pthread_mutex_unlock(&philo->global->mutex_global);
			philo->global->is_running = FALSE;
			return(TRUE);
		}
		else
			return(FALSE);
	}
	else
	{
		pthread_mutex_unlock(&philo->global->mutex_global);
		return(TRUE);
	}
	// finish this and test before adding 
}

long int get_time()
{
	struct timeval current_time;
	
	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	philo_eat(t_philo *philo)
{

	if (philo->global->tme + (get_time() - philo->time_since_last_meal) > philo->global->tmd)
	{
		usleep(philo->global->tmd - philo->time_since_last_meal);
		philo->global->is_running == FALSE;
	}
	else
	{
		usleep(philo->global->tme);	
		philo->time_since_last_meal = get_time();
	}
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->mutex_global);
	if (philo->global->is_running == TRUE)
	{
		pthread_mutex_unlock(&philo->global->mutex_global);
		usleep(1);
		printf("think"); // do think fct
	}
	else
	{
		usleep(1);
		pthread_mutex_unlock(&philo->global->mutex_global);
	}
}

void	my_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->mutex_global);
	if (philo->global->is_running == TRUE)
	{
		pthread_mutex_unlock(&philo->global->mutex_global);
		// philo_wait(philo, get_time());
		usleep(8000);
		printf("sleep"); // do sleeping fct
	}
	else
	{
		pthread_mutex_unlock(&philo->global->mutex_global);
	}
}

t_bool	eat(t_philo *philo)
{
	int left;
	int right;

	left = philo->index;
	if 
	while (TRUE)
	{
		pthread_mutex_lock(&philo->forks[philo->index].mutex);
		if(philo->forks->fork.mutex.__data.__lock == 0)
		{
			pthread_mutex_lock(&philo->forks[philo->index].fork.mutex);
			printf("take a fork\n");
			pthread_mutex_lock(&philo->global->mutex_global);
			if(philo->index == philo->global->nb_of_philos)
				pthread_mutex_lock(&philo->forks[0].fork.mutex);
			else
				pthread_mutex_lock(&philo->forks[philo->index + 1].fork.mutex);
			printf("take a fork\n");
			printf("philo eat");
			philo_wait(philo);
			pthread_mutex_lock(&philo->forks[philo->index].fork.mutex);
		}
	}
	printf("die\n"); // do philo_die fct
	return (FALSE); // PHILO DIE
}
// void	*cycle(void *arg)
// {
// 	t_philo		*philo;
// 	int		meal;

// 	meal = 0;
// 	philo = (t_philo *)arg;
// 	pthread_mutex_lock(&philo->global->mutex_global);
// 	while (philo->global->is_running == TRUE || philo->global->meal_before_death != meal)
// 	{
// 		// pthread_mutex_unlock(&philo->global->mutex_global);
// 		if(eat(philo))
// 			meal++;
// 		my_sleep(philo);
// 		think(philo);
// 		if(check_if_dead(philo, get_time()))
// 			break ;	
// 		pthread_mutex_lock(&philo->global->mutex_global);
// 	}
// 	// printf("out !\n");
// 	pthread_mutex_unlock(&philo->global->mutex_global);
// 	usleep(100);
// 	return(NULL);
// }

void *cycle(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	pthread_mutex_lock(&philo->forks[]->mutex);
	if (philo->forks->fork.mutex.__data.__lock == 0)
	{
		pthread_mutex_lock(&philo->)
		printf("philo %d, has taken fork %d\n")
	}
	return (NULL);
}

void	start_routine(t_philo **philos)
{
	int	i;
	int	max_philo;

	i = 0;
	max_philo =  philos[0]->global->nb_of_philos;
	while (i < max_philo)
	{
		pthread_create(&philos[i]->philo, NULL, cycle, &philos[i]);
		i++;
		usleep(50);
	}
}

int	main(int ac, char **av)
{
	t_philo **philos;
	t_secu_fork *forks;
	t_datas	*global;

	if (ac == 5 || ac == 6)
	{
		global = set_datas(av[1], av[2], av[3], av[4]);
		if (ac == 6)
			set_meal(global, av[5]);
		forks = set_forks(global);
		philos = set_philo(global, forks);
		start_routine(philos);
		// free(global);
	}
}



tmd = 800

tmslm = 500

tme = 400

