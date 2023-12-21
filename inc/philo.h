/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:35:19 by jolecomt          #+#    #+#             */
/*   Updated: 2023/12/21 20:05:22 by jolecomt         ###   ########.fr       */
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

typedef struct s_fork
{
	t_bool 			taken; 			// SET BY DEFAULT AS FALSE, IF A PHILO DIE SET AT TRUE 
	pthread_mutex_t		mutex;
}				t_fork;

typedef struct s_datas
{
	int			nb_of_philos;		// 1 or supp 
	int			meal_before_death;	// the number of meal before philo die
	struct timeval		time_at_start;		// get the time at the start
	long int		tmd;			// can be neg in mls
	long int		tme;			// can be neg in mls
	long int		tms;			// can be neg in mls
	t_bool			is_running;		// SET BY DEFAULT AS TRUE, IF A PHILO DIE SET AT FALSE 
	pthread_mutex_t		mutex_global;
}				t_datas;

typedef struct s_philo
{
	long int		time_since_last_meal;	// time
	int			index; 			// index of philo
	// t_state 		state;			// EAT or SLEEP or THINK
	t_fork			*forks;			// list of all the fork 
	t_datas 		*global;		// struct of global var needed
	pthread_t 		philo;			// thread of the philo
}				t_philo;

/*----philo.c----*/


#endif