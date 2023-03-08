/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:27:46 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/08 17:15:21 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <pthread.h>

static void	change_status(enum e_state status, t_philo *data, long int time)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mutex);
	if (status == start)
	{
	}
	if (status == sleeping)
	{
		data->state = sleeping;
		printf("\033[1;36m%li Philo %i start to sleep\n\033[0m", time, data->id);
	}
	if (status == eating)
	{
		data->state = eating;
		printf("\033[1;32m%li Philo %i start to eat\n\033[0m", time, data->id);
	}
	if (status == thinking)
	{
		data->state = thinking;
		printf("\033[1;35m%li Philo %i start to think\n\033[0m", time, data->id);
	}
	if (status == dead)
	{
		data->state = dead;
		printf("\033[1;31m%li Philo %i died\n\033[0m", time - 1, data->id);
	}
	pthread_mutex_unlock(&mutex);
}

static	void	*start_thd(void	*data)
{
	t_philo			*ph_data;
	long int		current_time;
	long int		last_change_t;

	ph_data = data;
	while (1)
	{
		current_time = get_set_time(2, ph_data);
		if (ph_data->state == start)
		{
			last_change_t = current_time;
			if (pthread_mutex_lock(&ph_data->forks[0]) == 0)
			{
				if (pthread_mutex_lock(&ph_data->forks[1]) == -1)
				{
					pthread_mutex_unlock(&ph_data->forks[0]);
					change_status(thinking, ph_data, current_time);
				}
				else
					change_status(eating, ph_data, current_time);
			}
			else
				change_status(thinking, ph_data, current_time);
		}
		if (ph_data->state == sleeping && (current_time - last_change_t) >= ph_data->t_sleep)
		{
			last_change_t = current_time;
			change_status(thinking, ph_data, current_time);
		}
		if (current_time > ph_data->t_die)
		{
			change_status(dead, ph_data, current_time);
			break ;
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		**philos;
	t_forks		*forks;
	pthread_t	*thd;
	int			i;

	if (ac < 5 || ac > 6)
	{
		write(2, "Wrong numbers of arguments\n", 27);
		return (0);
	}
	if (check_args(ac - 1, av + 1) == -1)
		return (-1);
	forks = init_forks(av[1]);
	if (!forks)
		return (-1);
	philos = init_philos(av + 1, ac - 1, forks);
	if (!philos)
		return (1);
	thd = malloc(sizeof(pthread_t) * forks->philo_nb);
	if (!thd)
	{
		free_philos(&philos, forks->philo_nb);
		free_forks(&forks);
		return (1);
	}
	i = 0;
	get_set_time(0, philos[0]);
	while (i < forks->philo_nb)
	{
		if (pthread_create(&thd[i], NULL, &start_thd, philos[i]) == -1)
		{
			free_philos(&philos, forks->philo_nb);
			free_forks(&forks);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < forks->philo_nb)
	{
		pthread_join(thd[i], NULL);
		i++;
	}
	return (0);
}
