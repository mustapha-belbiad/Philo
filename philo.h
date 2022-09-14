/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelbiad <mbelbiad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 02:21:02 by mbelbiad          #+#    #+#             */
/*   Updated: 2022/09/14 12:19:40 by mbelbiad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdatomic.h>

typedef struct t_philo
{
	int				num_philos;
	long			time_to_eat;
	int				time_to_die;
	long			time_to_sleep;
	int				num_of_eating;
	int				right;
	int				left;
	long			start;
	int				id;
	int				fn_phi;
	long			last_eat;
	int				eat;
	int				check_death;
	int				chk_print;
	pthread_mutex_t	*print;
	pthread_mutex_t *l_eat;
	pthread_mutex_t *n_eat;
	pthread_mutex_t	*fork;
}	t_philo;

int			ft_check(int ac, char *av[]);
int			put_vl(t_philo *phi, char **av, int ac);
long int	get_time(void);
void		*init_forks(t_philo *philo);
void		sleepy(long timming);
void    *init_forks(t_philo *philo);
void    ft_pthread(t_philo *phi);
int ft_check_death(t_philo *phi);

#endif