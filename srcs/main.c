/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:27:46 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/27 14:34:44 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <sys/select.h>

static	void	*start_thd(void *data)
{
	t_philo			*ph_data;
	struct timeval	actual_time;
	struct timeval	start_time;
	int				counter;

	start_time = get_set_starttime(1);
	ph_data = (t_philo *)data;
	while (1)
	{
		gettimeofday(&actual_time, NULL);
		counter = actual_time.tv_usec - start_time.tv_usec;
		if (ph_data->state != sleeping)
		{
			printf("\033[1;33m");
			printf("%i Philo %i is sleeping\n", counter - 1, ph_data->id);
			printf("\033[0m");
			ph_data->state = sleeping;
		}
		if (counter > ph_data->t_die)
		{
			printf("%i Philo %i died\n", counter - 1, ph_data->id);
			break ;
		}
	}
	return (NULL);
}

static void	join_threads(pthread_t *thd, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_join(thd[i], NULL);
		i++;
	}
	free(thd);
}

static void	init_threads(pthread_t *thd, t_philo **philos)
{
	int	i;

	i = 0;
	get_set_starttime(0);
	while (i < philos[0]->forks->philo_nb)
	{
		if (pthread_create(thd + i, NULL, &start_thd, philos[i]) == -1)
			join_threads(thd, philos[0]->forks->philo_nb);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo		**philos;
	pthread_t	*thd;

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
	init_threads(thd, philos);
	join_threads(thd, philos[0]->forks->philo_nb);
	free_philos(&philos);
	return (0);
}
