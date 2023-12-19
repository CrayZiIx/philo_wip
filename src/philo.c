/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolecomt <jolecomt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:26:48 by jolecomt          #+#    #+#             */
/*   Updated: 2023/12/19 17:44:51 by jolecomt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_philo *philos;
	t_datas	*global;

	if (ac == 5)
	{
		set_datas(av[1], av[2], av[3], av[4]);
		set_philo(philos, global);
	}
}