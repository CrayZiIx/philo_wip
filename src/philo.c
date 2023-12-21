/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:26:48 by jolecomt          #+#    #+#             */
/*   Updated: 2023/12/21 20:32:09 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_fork(t_bool *value, t_philo *philo, int index)
{
	pthread_mutex_lock(&philo->forks[index].mutex);
	if (philo->forks[index].taken == FALSE)
	{
		philo->forks[index].taken = TRUE;
		value = TRUE;
		printf("%d has taken a fork\n", philo->index); // add timestamp
	}
	pthread_unlock(&philo->forks[index].mutex);
}
t_bool check_if_dead(t_philo *philo, long int current_time)
{
	pthread_mutex_lock(&philo->global->mutex_global)
	if (philo->global->is_running)
	// finish this and test before adding 
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
		pthread_mutex_unlock(&philo->global->mutex_global);
	}
}

void	sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->mutex_global);
	if (philo->global->is_running == TRUE)
	{
		pthread_mutex_unlock(&philo->global->mutex_global);
		philo_wait(philo, get_time());
		printf("sleep"); // do sleeping fct
	}
	else
	{
		pthread_mutex_unlock(&philo->global->mutex_global);
		return (FALSE);
	}
}

t_bool	eat(t_philo *philo)
{
	t_bool left;
	t_bool right;

	left = FALSE;
	right = FALSE;
	while (TRUE)
	{
		usleep(1);
		if((left == FALSE && right == FALSE)) // || check_if_dead(philo, get_time()) 
		{
			pthread_mutex_lock(&philo->global->mutex_global);	
			take_fork(&left, philo, philo->index);
			if (philo->index == philo->global->nb_of_philos - 1) // if -> go with 0, else go with philo->index + 1
				take_fork(&right, philo, 0);
			else
				take_fork(&right, philo, philo->index + 1);
			pthread_mutex_unlock(&philo->global->mutex_global);
			printf("eat\n"); // do philo_eat fct
			return(TRUE); // SUCCESS
		}
		if(check_if_dead(philo, get_time()))
			break ;
	}
	printf("die\n"); // do philo_die fct
	return (FALSE); // PHILO DIE
}
void	*cycle(void *arg)
{
	t_philo		*philo;
	int		meal;

	meal = 0;
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->global->mutex_global);
	while (philo->global->is_running == TRUE || philo->global->meal_before_death != meal)
	{
		pthread_mutex_unlock(&philo->global->mutex_global);
		if(eat(philo))
			meal++;
		sleep(philo);
		think(philo);
		if(check_if_dead(philo, get_time()))
			break ;	
		pthread_mutex_lock(&philo->global->mutex_global);
	}
	pthread_mutex_unlock(&philo->global->mutex_global);
	usleep(100);
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
	i = 0;
	while (i < max_philo)
		pthread_join(&philos[i++], NULL);
	i = 0;
	free(philos[0]->forks);
	while (i < max_philo)
		free(philos[i++]);
}

void	set_philo(t_philo **philos, t_datas *global)
{
	int	i;
	t_fork	*forks;

	i = 0;
	philos = malloc(sizeof(t_philo *) * global->nb_of_philos);
	forks = malloc(sizeof(t_fork) * global->nb_of_philos);
	while (i < global->nb_of_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		philos[i]->index = i;
		philos[i]->time_since_last_meal = global->time_at_start.tv_usec;
		philos[i]->forks = forks;
		pthread_mutex_init(&philos[i]->forks[i].mutex, NULL);
		philos[i]->global = global;
		i++;
	}
}

void	set_meal(t_datas *global, char *av5)
{
	global->meal_before_death = ft_atoi(av5);
}

t_datas *set_datas(char *av1, char *av2, char *av3, char *av4)
{
	t_datas *global;
	
	global = malloc(sizeof(t_datas));
	global->is_running = TRUE;
	global->nb_of_philos = ft_atoi(av1);
	global->meal_before_death = -1;
	gettimeofday(&global->time_at_start, NULL);
	global->tmd = ft_atoi(av2);
	global->tme = ft_atoi(av3);
	global->tms = ft_atoi(av4);
	return(global);
}

int	main(int ac, char **av)
{
	t_philo **philos;
	t_datas	*global;

	if (ac == 5 || ac == 6)
	{
		global = set_datas(av[1], av[2], av[3], av[4]);
		if (ac == 6)
			set_meal(global, av[5]);
		set_philo(philos, global);
		start_routine(philos);
		free(global);
	}
}