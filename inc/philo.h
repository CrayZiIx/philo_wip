/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:35:19 by jolecomt          #+#    #+#             */
/*   Updated: 2023/12/16 03:48:38 by jolecomt         ###   ########.fr       */
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

typedef struct s_forks
{
	t_bool taken;
	struct timeval entry;
	struct timeval exit;
	pthread_mutex_t	mutex;
}				t_forks;

typedef struct s_datas
{
	int	nb_of_philos;
	int	tmd;
	int	tme;
	int	tms;
}				t_datas;

typedef struct s_philo
{
	int	index;
	int	hmmtd; // how many meal to die
	int philo_tmd;
	int philo_tme;
	int philo_tms;
	t_state state;
	t_forks fork;
	pthread_t philo;
	t_datas *gdata;
	
}				t_philo;

/*----philo.c----*/


#endif