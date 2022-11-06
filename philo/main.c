/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:58:45 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/20 22:22:14 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	long int		time;
	struct timeval	mytime;

	if (gettimeofday(&mytime, NULL) == -1)
		return (0);
	time = (mytime.tv_sec * 1000) + (mytime.tv_usec / 1000);
	return (time);
}

void	sleepy(long timming)
{
	long	time;

	time = get_time();
	while (get_time() - time < timming)
		usleep(100);
}

int	ft_check_eating(t_philo *phi)
{
	int	i;

	i = 0;
	while (i < phi->num_philos)
	{
		pthread_mutex_lock(phi[i].n_eat);
		if (phi[i].eat != phi->num_of_eating)
		{
			pthread_mutex_unlock(phi[i].n_eat);
			return (1);
		}
		pthread_mutex_unlock(phi[i].n_eat);
		i++;
	}
	return (0);
}

int	ft_check_death(t_philo *phi)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(phi[i].l_eat);
		if (get_time() - phi[i].last_eat > phi[i].time_to_die)
		{
			pthread_mutex_unlock(phi[i].l_eat);
			pthread_mutex_lock(phi->print);
			printf("%ld philo %d is dead \n", get_time() - phi[i].start,
				phi[i].id);
			return (0);
		}
		else
		{
			pthread_mutex_unlock(phi[i].l_eat);
			if (ft_check_eating(phi) == 0)
				return (0);
		}
		i++;
		if (i == phi->num_philos)
			i = 0;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*phi;

	if (ac <= 4 || ac > 6 || ft_check(ac, av) == 0)
	{
		write(2, "Error\n", 7);
		return (0);
	}
	phi = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	if (put_vl(phi, av, ac) == 0)
		return (0);
	init_forks(phi);
	ft_pthread(phi);
	if (phi->num_philos > 0)
	{
		if (ft_check_death(phi) == 0)
		{
			ft_detach_thread(phi);
			return (0);
		}
	}
	return (0);
}
