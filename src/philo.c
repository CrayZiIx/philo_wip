/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:36:55 by jolecomt          #+#    #+#             */
/*   Updated: 2023/12/16 05:43:31 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_bool is_digit(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
	
}
t_bool check_args(int ac, char **av)//av[1], av[2], av[3], av[4]
{
	int i;

	i = 1;
	if ( ac == 5)
	{
		while (i != 4)
		{
			if (is_digit(av[i]) == TRUE)
				i++;
			else
				return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
}

t_datas	*set_datas(char *nb_of_philos, char *tmd, char *tme, char *tms)//av[1], av[2], av[3], av[4])
{
	t_datas *global;
	
	global = malloc(sizeof(t_datas));
	if (!global)
		return (NULL); // need to manage error if malloc crash
	global->nb_of_philos = ft_atoi(nb_of_philos);
	global->tmd = ft_atoi(tmd);
	global->tme = ft_atoi(tme);
	global->tms = ft_atoi(tms);
	return (global);
}

void	set_philos(t_philo *philos, t_datas *global)
{
	int	i;
	
	i = 0;
	while (i < global->nb_of_philos)
	{
		// memset(&philos[i].fork.mutex, 0, sizeof(pthread_mutex_t));
		philos[i].index = i; // rm
		philos[i].gdata = global;
		i++;
	}
}

void	go_sleep(t_philo *tmp)
{
	struct timeval entry;
	struct timeval exit;
	
	pthread_mutex_lock(&(tmp->fork.mutex));
	gettimeofday(&entry, NULL);
	usleep(tmp->gdata->tms);
	gettimeofday(&exit, NULL);
	tmp->philo_tms = exit.tv_usec - entry.tv_usec;
	pthread_mutex_unlock(&(tmp->fork.mutex));
	// think how to mutex all data in struct before using it 

}

void	*routine(void *arg)
{
	t_philo *tmp;

	tmp = (t_philo *) arg;
	if (tmp->state == EAT)
		go_sleep(tmp);
	else if (tmp->state == SLEEP)
		go_think(tmp);
	else
		go_eat(tmp); 
	return (NULL);
}

void	start_routine(t_philo *philos, t_datas *global)
{
	int				i;
	pthread_t tmp;
	
	i = 0;
	while (i < global->nb_of_philos)
	{
		tmp = philos[i].philo;
		pthread_mutex_init(&philos[i].fork.mutex, NULL);
		pthread_create(tmp, NULL, routine, &philos[i].fork.mutex);
		pthread_join(tmp, NULL);
	}
}
void	philo(t_datas *global)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * global->nb_of_philos);
	if (!global)
		return ; // need to manage error if malloc crash
	set_philos(philos, global);
	start_routine(philos, global);
	destroy_routine(philos, global);
}
int	main(int ac, char **av)
{
	t_datas *global;

	if (ac == 5)
	{
		if (check_args(ac, av) == TRUE)
		{
			global = set_datas(av[1], av[2], av[3], av[4]);
			philo(global);
		}
		else
		{
			write(1, "philo args are invalid try : 5 800 200 200 to test it !\n", 57);
			return (1);
		}
	}
	else
	{
		write(1, "philo need -> {nb_of_philo} {tmd} {tme} {tms} to work !\n", 57);
		write(1,"you can add {nb_of_time_each_philo_eat}\n",41);
		return (1);
	}
	return (0);
}
