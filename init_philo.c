/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 15:34:37 by jolecomt          #+#    #+#             */
/*   Updated: 2023/12/22 16:35:57 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	**set_philo(t_datas *global, t_secu_fork *forks)
{
	int		i;
	t_philo 	**philos;

	i = 0;
	philos = malloc(sizeof(t_philo *) * global->nb_of_philos);
	while (i < global->nb_of_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		philos[i]->index = i;
		philos[i]->time_since_last_meal = global->time_at_start;
		philos[i]->forks = forks;
		philos[i]->global = global;
		i++;
	}
	return (philos);
}

void	set_meal(t_datas *global, char *av5)
{
	global->meal_before_death = atoi(av5);
}

t_datas *set_datas(char *av1, char *av2, char *av3, char *av4)
{
	t_datas *global;
	struct timeval	tmp;
	
	global = malloc(sizeof(t_datas));
	global->is_running = TRUE;
	global->nb_of_philos = atoi(av1);
	global->meal_before_death = -1;
	gettimeofday(&tmp, NULL);
	global->time_at_start = tmp.tv_sec * 1000 + tmp.tv_usec / 1000;
	pthread_mutex_init(&global->mutex_global, NULL);
	global->tmd = atoi(av2);
	global->tme = atoi(av3);
	global->tms = atoi(av4);
	return(global);
}

t_secu_fork *set_forks(t_datas *global)
{
	int i;
	t_secu_fork *forks;

	forks = malloc(sizeof(t_fork) * global->nb_of_philos);
	while (i < global->nb_of_philos)
	{
		pthread_mutex_init(&forks[i].fork.mutex, NULL);
		pthread_mutex_init(&forks[i].mutex, NULL);
		i++;
	}
	return(forks);
}