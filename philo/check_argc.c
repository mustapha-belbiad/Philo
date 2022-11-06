/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:55:58 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/20 22:21:31 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check(int ac, char *av[])
{
	int	i;
	int	j;

	i = ac;
	while (i-- != 1)
	{
		j = 0;
		if (av[i][j] == '-')
			return (0);
		if (av[i][j] == '\0')
			return (0);
		if (av[i][j] == '+')
			j++;
		while (av[i][j] != '\0')
		{
			if (av[i][j] < 48 || av[i][j] > 57)
				return (0);
			j++;
		}
	}
	return (1);
}

void	ft_detach_thread(t_philo *phi)
{
	int	i;

	i = 0;
	while (i < phi->num_philos)
	{
		pthread_detach(phi[i].ph);
		i++;
	}
}
