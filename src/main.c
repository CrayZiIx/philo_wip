/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:36:11 by jolecomt          #+#    #+#             */
/*   Updated: 2023/12/22 19:07:20 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*FCT*/
long int get_time()
{
	struct timeval current_time;
	
	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->left].mutex);
	if (philo->global->is_running == TRUE)
		printf("%ld %d has taken a fork\n", get_time(), philo->left);
	pthread_mutex_lock(&philo->forks[philo->right].mutex);
	if (philo->global->is_running == TRUE)
		printf("%ld %d has taken a fork\n", get_time(), philo->left);
	pthread_mutex_lock(&philo->meal.mutex);
	philo->meal.data++;
	// usleep(10);
	// printf("test\n");
	pthread_mutex_unlock(&philo->meal.mutex);
	printf("%d %ld eat\n", philo->left, get_time());
	usleep(philo->global->tme);
	pthread_mutex_unlock(&philo->forks[philo->left].mutex);
	pthread_mutex_unlock(&philo->forks[philo->right].mutex);
}

/*CYCLE & DEATH*/
void	*cycle(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// printf("t\n");
	pthread_mutex_lock(&philo->global->mutex_global);
	while (philo->global->is_running == TRUE)
	{
		pthread_mutex_unlock(&philo->global->mutex_global);
		take_fork(philo);
		printf("%d %ld sleep\n", philo->left, get_time());
		usleep(philo->global->tms);
		printf("%d %ld think\n", philo->left, get_time());
		// usleep(1);
		pthread_mutex_lock(&philo->global->mutex_global);
	}
	pthread_mutex_unlock(&philo->global->mutex_global);
	return (NULL);
}	

void	*death(void *arg)
{
	t_philo		*death;
	long int	new_time;
	// int meal;

	death = (t_philo *)arg;
	// meal = 0;	
	pthread_mutex_lock(&death->global->mutex_global);
	while (death->global->is_running == TRUE)
	{
		usleep(50);
		pthread_mutex_lock(&death->meal.mutex);	
		if (death->meal.data == death->global->meal_before_death)
		{
			pthread_mutex_unlock(&death->meal.mutex);	
			death->global->is_running = FALSE;
			break ;
		}
		pthread_mutex_unlock(&death->meal.mutex);	
		// meal++;
		pthread_mutex_lock(&death->timer_last_meal.mutex);
		new_time = death->timer_last_meal.timer;
		pthread_mutex_unlock(&death->timer_last_meal.mutex);
		if (new_time + death->global->tme > new_time + death->global->tmd)
			death->global->is_running = FALSE;
		else
			new_time += death->global->tme;
		if (new_time + death->global->tms > new_time + death->global->tmd)
			death->global->is_running = FALSE;
		else
			new_time += death->global->tms;
		pthread_mutex_unlock(&death->global->mutex_global);
		usleep(15);
	}
	pthread_mutex_unlock(&death->global->mutex_global);
	printf("die\n");
	return (NULL);
}
/*START CYCLE & DEATH*/

void start_cycle_death(t_philo *philo)
{
	int	i;
	int	max_philo;

	// printf("t\n");
	i = 0;
	max_philo = philo[0].global->nb_of_philos;
	while (i < max_philo)
	{
		pthread_create(&philo[i].philo, NULL, cycle, &philo[i]);
		pthread_create(&philo[i].death, NULL, death, &philo[i]);
		i++;
		// usleep(50);
	}
	i = 0;
	while (i < max_philo)
	{
		pthread_join(philo[i].philo, NULL);
		pthread_join(philo[i].death, NULL);
		i++;
	}
}

/*INIT PART*/
t_datas *set_datas(char *av1, char *av2, char *av3, char *av4)
{
	t_datas *global;
	struct timeval	tmp;
	
	global = malloc(sizeof(t_datas));
	gettimeofday(&tmp, NULL);
	global->is_running = TRUE;
	global->nb_of_philos = atoi(av1); // change for ft_atoi
	global->meal_before_death = -1;
	global->tmd = atoi(av2); // change for ft_atoi
	global->tme = atoi(av3); // change for ft_atoi
	global->tms = atoi(av4); // change for ft_atoi 
	pthread_mutex_init(&global->mutex_global, NULL);
	return(global);
}
void	set_meal(t_datas *global, char *av5)
{
	global->meal_before_death = atoi(av5);
}

t_fork *set_forks(t_datas *global)
{
	int i;
	t_fork *forks;

	forks = malloc(sizeof(t_fork) * global->nb_of_philos);
	while (i < global->nb_of_philos)
	{
		pthread_mutex_init(&forks[i].mutex, NULL);
		i++;
	}
	return(forks);
}

t_philo *set_philos(t_datas *global, t_fork *forks)
{
	t_philo *philo;
	int	i;
	struct timeval	time;

	i = 0;

	gettimeofday(&time, NULL);
	philo = malloc(sizeof(t_philo) * global->nb_of_philos);
	while (i < global->nb_of_philos)
	{
		philo[i].meal.data = 0;
		pthread_mutex_init(&philo[i].meal.mutex, NULL);
		philo[i].left = i;
		if (i == global->nb_of_philos - 1)
			philo[i].right = 0;
		else
			philo[i].right = i + 1;
		philo[i].forks = forks;
		philo[i].global = global;
		philo[i].timer_last_meal.timer = time.tv_sec * 1000 + time.tv_usec/1000;
		pthread_mutex_init(&philo[i].timer_last_meal.mutex ,NULL);
		i++;
	}
	return (philo);
}

/*MAIN*/
int	main(int ac, char **av)
{
	t_philo *philos;
	t_fork *forks;
	t_datas	*global;

	if (ac == 5 || ac == 6)
	{
		global = set_datas(av[1], av[2], av[3], av[4]);
		if (ac == 6)
			set_meal(global, av[5]);
		forks = set_forks(global);
		philos = set_philos(global, forks);
		// printf("t\n");
		start_cycle_death(philos);
		// free(global);
	}
}

// 100 0 1