/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:58:45 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/14 12:57:21 by mbelbiad         ###   ########.fr       */
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
	long    time;

	time = get_time();
	while (get_time() - time < timming)
		usleep(100);
	// long	time;
	// time = get_time();
	// usleep(timming * 1000 - 20000);
	// while (get_time() - time < timming)
	//     ;
}

// void    ft_printf(t_philo *philo, int num)
// {
// 	if (num == 1)
// 	{
// 		pthread_mutex_lock(philo->print);
// 	   // printf("=== > %d \n", philo->id);
// 		printf("%ld philo %d take a fork\n", get_time() - philo->start, philo->id);
// 		pthread_mutex_unlock(philo->print);
// 	}
// 	else if (num == 2)
// 	{
// 		pthread_mutex_lock(philo->print);
// 		//printf("=== > %d \n", philo->id);
// 		// philo->eat += 1;
// 		printf("%ld philo %d is eating\n", get_time() - philo->start, philo->id);
// 		//printf(" >>>> = %d \n", philo->eat);
// 		pthread_mutex_unlock(philo->print);
// 	}
// 	else if (num == 3)
// 	{
// 		pthread_mutex_lock(philo->print);
// 	   // printf("=== > %d \n", philo->id);
// 		printf("%ld philo %d is sleeping\n", get_time() - philo->start, philo->id);
// 		pthread_mutex_unlock(philo->print);
// 	}
// 	else if (num == 4)
// 	{
// 		pthread_mutex_lock(philo->print);
// 	   // printf("=== > %d \n", philo->id);
// 		printf("%ld philo %d is thinking\n", get_time() - philo->start, philo->id);
// 		pthread_mutex_unlock(philo->print);
// 	}
// }

// int check_eating(t_philo *phi)
// {
//     if (phi->num_of_eating == (phi->eat * phi->num_philos))
//         return (0);
//     else 
//         return(1);
// }
// void *test(void *philo)
// {
// 	t_philo *phi;
// 	pthread_mutex_t eat;
// 	pthread_mutex_init(&eat, NULL);
// 	phi = (t_philo *)philo;
// 	//  printf(" ==+=> %d\n", phi->left);
// 	//  printf(" ==+=> %d\n", phi->right);
// 	while(1)
// 	{
// 		if(phi->eat == (phi->num_philos * phi->num_of_eating))
// 			break ;
// 		pthread_mutex_lock(&phi->fork[phi->left]);
// 		ft_printf(phi, 1);
// 		pthread_mutex_lock(&phi->fork[phi->right]);
// 		phi->last_eat = get_time();
// 		ft_printf(phi, 1);
// 		ft_printf(phi, 2);
// 		//usleep(phi->time_to_eat * 1000);
// 		//phi->eat += 1;
// 		sleepy(phi->time_to_eat);
// 		pthread_mutex_unlock(&phi->fork[phi->left]);
// 		pthread_mutex_unlock(&phi->fork[phi->right]);
// 		if (phi->num_of_eating != -1)
// 		{
// 			pthread_mutex_lock(&eat);
// 			phi->eat++;
// 			pthread_mutex_unlock(&eat);
// 		}
// 		if(phi->eat == phi->num_of_eating)
// 		{
// 			// printf("==> %d \n", phi->eat);
// 			// printf("==> %d \n", phi->num_of_eating);
// 			break ;
// 		}
// 		ft_printf(phi, 3);
// 		//usleep(phi->time_to_sleep * 1000);
		
// 		sleepy(phi->time_to_sleep);
// 		ft_printf(phi, 4);
// 	 }
// 	return(0);
// }

int ft_check_eating(t_philo *phi)
{
	int i;

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
int ft_check_death(t_philo *phi)
{
	// pthread_mutex_t l;

	// pthread_mutex_init(&l, NULL);
	int i;
 
	i = 0;
	while(1)
	{
		pthread_mutex_lock(phi[i].l_eat);
		if (get_time() - phi[i].last_eat > phi[i].time_to_die)
		{
			pthread_mutex_unlock(phi[i].l_eat);
			pthread_mutex_lock(phi->print);
			printf("%ld philo %d is dead \n", get_time() - phi[i].start, phi[i].id);
			return(0);
		}
		else
		{
			pthread_mutex_unlock(phi[i].l_eat);
			if (ft_check_eating(phi) == 0)
				break ;
		}
		i++;
		if (i == phi->num_philos)
			i = 0;
	}
	//pthread_mutex_unlock(&l);
	return (0);
}

// void    ft_pthread(t_philo *phi)
// {
// 	pthread_t ph;
// 	int i;

// 	i = 0;
// 	while (i < phi->num_philos)
// 	{
// 		pthread_create(&ph, NULL, &test, &phi[i]);
// 		i += 2;
// 	}
// 	usleep(phi->num_philos * 50);
// 	i = 1;
// 	while (i < phi->num_philos)
// 	{
// 		pthread_create(&ph, NULL, &test, &phi[i]);
// 		i += 2;
// 	}
// }

int main (int ac, char **av)
{  
	t_philo *phi;

	if (ac <= 4 || ac > 6 || ft_check(ac, av) == 0)
	{
		write(2, "Error\n", 7);
		return(0);
	}

	phi = malloc(sizeof(t_philo) * atoi(av[1]));
	if (put_vl(phi, av, ac) == 0)
		return(0);
	//phi->chk_print = 1;
	init_forks(phi);

	ft_pthread(phi);
	if (phi->num_philos > 0)
		ft_check_death(phi);
	return(0);
}