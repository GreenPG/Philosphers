/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:27:46 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/07 16:34:40 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <pthread.h>

static	void	*start_thd(void	*data)
{
	pthread_mutex_t	mutex;
	t_philo			*ph_data;
	long int		start_time;
	long int		current_time;

	pthread_mutex_init(&mutex, NULL);
	start_time = get_set_time(0);
	ph_data = data;
	while (1)
	{
		current_time = get_set_time(1) - start_time;
		if (ph_data->state == start)
		{
			pthread_mutex_lock(&mutex);
			ph_data->state = thinking;
			printf("\033[1;31m%li Philo %i start to think\n", current_time, ph_data->id);
			printf("\033[0m");
			pthread_mutex_unlock(&mutex);
		}
		if (current_time > ph_data->t_die)
		{
			pthread_mutex_lock(&mutex);
			printf("\033[1;31m%li Philo %i died\n", current_time - 1, ph_data->id);
			printf("\033[0m");
			pthread_mutex_unlock(&mutex);
			break ;
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		**philos;
	pthread_t	*thd;
	int			i;

	if (ac < 5 || ac > 6)
	{
		write(2, "Wrong numbers of arguments\n", 27);
		return (0);
	}
	if (check_args(ac - 1, av + 1) == -1)
		return (-1);
	philos = init_philos(av + 1, ac - 1);
	if (!philos)
		return (1);
	thd = malloc(sizeof(pthread_t) * philos[0]->forks->philo_nb);
	if (!thd)
	{
		free_philos(&philos);
		return (1);
	}
	i = 0;
	while (i < philos[0]->forks->philo_nb)
	{
		if (pthread_create(&thd[i], NULL, &start_thd, philos[i]) == -1)
		{
			free_philos(&philos);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < philos[0]->forks->philo_nb)
	{
		pthread_join(thd[i], NULL);
		i++;
	}
	return (0);
}
