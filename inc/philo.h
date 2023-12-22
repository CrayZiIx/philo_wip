/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:35:19 by jolecomt          #+#    #+#             */
/*   Updated: 2023/12/22 19:06:22 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*----INCLUDE----*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h> 

/*----TYPEDEF----*/

typedef enum t_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef enum t_state
{
	EAT,
	SLEEP,
	THINK
}				t_state;

typedef struct 			s_fork
{
	int			data;
	pthread_mutex_t		mutex;
}				t_fork;

typedef struct 			s_timer
{
	long int		timer;
	pthread_mutex_t		mutex;
}				t_timer;

typedef struct s_datas
{
	int			nb_of_philos;		// 1 or supp 
	int			meal_before_death;	// the number of meal before philo die	
	// long int		time_at_start;		// get the time at the start
	long int		tmd;			// can be neg in mls
	long int		tme;			// can be neg in mls
	long int		tms;			// can be neg in mls
	long int		time_at_start;		// time at stat
	t_bool			is_running;		// SET BY DEFAULT AS TRUE, IF A PHILO DIE SET AT FALSE 
	pthread_mutex_t		mutex_global;
}				t_datas;

typedef struct	s_death
{
	pthread_t	death;
}		t_death;

typedef struct s_philo
{
	t_fork			meal;
	t_timer			timer_last_meal;	// time
	int			left; 			// index of left fork
	int			right; 			// index of right fork
	t_fork			*forks;			// the fork of the philo
	t_datas 		*global;		// struct of global var needed
	pthread_t 		philo;			// thread of the philo
	pthread_t 		death;			// thread of the death
}				t_philo;

/*----philo.c----*/


// -fsanitize=thread

#endif