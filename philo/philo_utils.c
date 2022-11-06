/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 04:09:46 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/20 20:33:19 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 1;
	k = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = j * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		k = k * 10 + str[i] - '0';
		i++;
	}
	return (k * j);
}

void	init_threads_0(t_philo *phi, int i, int ac, char **av)
{
	phi[i].num_philos = ft_atoi(av[1]);
	phi[i].time_to_die = ft_atoi(av[2]);
	phi[i].time_to_eat = ft_atoi(av[3]);
	phi[i].time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		phi[i].num_of_eating = ft_atoi(av[5]);
	else
		phi[i].num_of_eating = -1;
}

void	ft_init_threads(char **av, t_philo *phi, int ac, pthread_mutex_t *p)
{
	int	i;

	i = -1;
	phi[0].l_eat = malloc(sizeof(pthread_mutex_t));
	phi[0].ph = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	pthread_mutex_init(phi[0].l_eat, NULL);
	phi[0].n_eat = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(phi[0].n_eat, NULL);
	while (++i < ft_atoi(av[1]))
	{
		init_threads_0(phi, i, ac, av);
		phi[i].start = get_time();
		phi[i].id = i + 1;
		phi[i].check_death = ft_atoi(av[2]);
		phi[i].left = i;
		phi[i].right = (i + 1) % phi->num_philos;
		phi[i].print = p;
		if (i > 0)
			phi[i].l_eat = phi[0].l_eat;
		if (i > 0)
			phi[i].n_eat = phi[0].n_eat;
		phi[i].ph = phi[0].ph;
		phi[i].eat = 0;
		phi[i].last_eat = phi[i].start;
	}
}

int	put_vl(t_philo *phi, char **av, int ac)
{
	int				i;
	pthread_mutex_t	*p;

	i = 0;
	p = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(p, NULL);
	ft_init_threads(av, phi, ac, p);
	phi->fn_phi = ft_atoi(av[1]);
	phi->chk_print = 1;
	if (phi->num_philos == 0 || phi->num_of_eating == 0)
		return (0);
	return (1);
}

void	*init_forks(t_philo *philo)
{
	int				i;
	pthread_mutex_t	*fork;

	fork = malloc(philo->num_philos * sizeof(pthread_mutex_t));
	i = 0;
	while (i < philo->num_philos)
		pthread_mutex_init(&fork[i++], NULL);
	i = 0;
	while (i < philo->num_philos)
	{
		philo[i].fork = fork;
		i++;
	}
	return (philo->fork);
}
