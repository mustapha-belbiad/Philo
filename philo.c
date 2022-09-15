/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 21:25:12 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/15 23:21:40 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printf2(t_philo *philo, int num)
{
	if (num == 3)
	{
		pthread_mutex_lock(philo->print);
		printf("%ld philo %d is sleeping\n",
			get_time() - philo->start, philo->id);
		pthread_mutex_unlock(philo->print);
	}
	else if (num == 4)
	{
		pthread_mutex_lock(philo->print);
		printf("%ld philo %d is thinking\n",
			get_time() - philo->start, philo->id);
		pthread_mutex_unlock(philo->print);
	}
}

void	ft_printf(t_philo *philo, int num)
{
	if (num == 1)
	{
		pthread_mutex_lock(philo->print);
		printf("%ld philo %d take a fork\n",
			get_time() - philo->start, philo->id);
		pthread_mutex_unlock(philo->print);
	}
	else if (num == 2)
	{
		pthread_mutex_lock(philo->print);
		printf("%ld philo %d is eating\n",
			get_time() - philo->start, philo->id);
		pthread_mutex_unlock(philo->print);
	}
	else
		ft_printf2(philo, num);
}

int	ft_chek_eating(t_philo *phi)
{
	pthread_mutex_t	eat;

	pthread_mutex_init(&eat, NULL);
	if (phi->num_of_eating != -1)
		{
			pthread_mutex_lock(phi->n_eat);
			phi->eat++;
			pthread_mutex_unlock(phi->n_eat);
		}
	if (phi->eat == phi->num_of_eating)
		return(0) ;
	else
		return(1);
}	

void	*test(void *philo)
{
	t_philo			*phi;
	// pthread_mutex_t	eat;

	// pthread_mutex_init(&eat, NULL);
	phi = (t_philo *)philo;
	while (1)
	{
		if (phi->eat == (phi->num_philos * phi->num_of_eating))
			break ;
		pthread_mutex_lock(&phi->fork[phi->left]);
		ft_printf(phi, 1);
		pthread_mutex_lock(&phi->fork[phi->right]);
		pthread_mutex_lock(phi->l_eat);
		phi->last_eat = get_time();
		pthread_mutex_unlock(phi->l_eat);
		ft_printf(phi, 1);
		ft_printf(phi, 2);
		sleepy(phi->time_to_eat);
		pthread_mutex_unlock(&phi->fork[phi->left]);
		pthread_mutex_unlock(&phi->fork[phi->right]);
		// if (phi->num_of_eating != -1)
		// {
		// 	pthread_mutex_lock(phi->n_eat);
		// 	phi->eat++;
		// 	pthread_mutex_unlock(phi->n_eat);
		// }
		// if (phi->eat == phi->num_of_eating)
		// 	break ;
		if (ft_chek_eating(phi) == 0)
			break;
		ft_printf(phi, 3);
		sleepy(phi->time_to_sleep);
		ft_printf(phi, 4);
	}
	return (0);
}

void	ft_pthread(t_philo *phi)
{
	//pthread_t	ph;
	int			i;

	i = 0;
	//ph = malloc(sizeof(pthread_t) * phi->num_philos);
	// phi[0].ph = malloc(sizeof(pthread_t));
	// while (i < phi->num_philos)
	// {
	// 	phi[i].ph = ph;
	// }
	while (i < phi->num_philos)
	{
		pthread_create(&phi[i].ph, NULL, &test, &phi[i]);
		usleep(60);
		i += 1;
		//pthread_join(phi[i].ph, NULL);
	}
	// usleep(60);
	// i = 1;
	// while (i < phi->num_philos)
	// {
	// 	pthread_create(&phi[i].ph, NULL, &test, &phi[i]);
	// 	i += 2;
	// 	//pthread_join(ph, NULL);
	// }
	// if (phi->num_philos > 0)
	// 	ft_check_death(phi);
	//  i = 0;
	// while(i < phi->num_philos)
	// {
	// 	pthread_join(phi[i].ph, NULL);
	// 	i++;
	// }
	// i = 0;
	// while(i < phi->num_of_eating)
	// {
	// 	pthread_mutex_destroy(phi[i].fork);
	// 	pthread_mutex_destroy(phi[i].l_eat);
	// 	pthread_mutex_destroy(phi[i].n_eat);
	// 	pthread_mutex_destroy(phi[i].print);
	// 	i++;
	// }
}