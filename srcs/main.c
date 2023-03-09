/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:27:46 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/09 16:28:27 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	change_status(enum e_state status, t_philo *data, long int time)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mutex);
	if (status != take)
		data->state = status;
	if (status == take)
		printf("\033[1;33m%li Philo %i has taken a fork\n\033[0m", time, data->id);
	else if (status == sleeping)
		printf("\033[1;36m%li Philo %i start to sleep\n\033[0m", time, data->id);
	else if (status == eating)
		printf("\033[1;32m%li Philo %i start to eat\n\033[0m", time, data->id);
	else if (status == thinking)
		printf("\033[1;35m%li Philo %i start to think\n\033[0m", time, data->id);
	else
		printf("\033[1;31m%li Philo %i died\n\033[0m", time - 1, data->id);
	pthread_mutex_unlock(&mutex);
}

static void	launcher(t_philo **philos, t_forks *forks, pthread_t *thd)
{
	int			i;

	i = 0;
	get_set_time(0, philos[0]);
	while (i < forks->philo_nb)
	{
		if (pthread_create(&thd[i], NULL, &start_thd, philos[i]) == -1)
		{
			free_philos(&philos, forks->philo_nb);
			free_forks(&forks);
			return ;
		}
		i++;
	}
}

static void	end_thread(t_philo **philos, t_forks *forks, pthread_t *thd)
{
	int	i;

	i = 0;
	while (i < forks->philo_nb)
	{
		pthread_join(thd[i], NULL);
		i++;
	}
	free_philos(&philos, forks->philo_nb);
	free_forks(&forks);
}

static pthread_t	*create_thd(t_philo **philos, t_forks *forks)
{
	pthread_t	*thd;

	thd = malloc(sizeof(pthread_t) * forks->philo_nb);
	if (!thd)
	{
		free_philos(&philos, forks->philo_nb);
		free_forks(&forks);
		exit (1);
	}
	return (thd);
}

int	main(int ac, char **av)
{
	t_philo		**philos;
	t_forks		*forks;
	pthread_t	*thd;

	if (ac < 5 || ac > 6)
	{
		write(2, "Wrong numbers of arguments\n", 27);
		return (0);
	}
	if (check_args(ac - 1, av + 1) == -1)
		return (1);
	forks = init_forks(av[1]);
	if (!forks)
		return (1);
	philos = init_philos(av + 1, ac - 1, forks);
	if (!philos)
		return (1);
	thd = create_thd(philos, forks);
	launcher(philos, forks, thd);
	end_thread(philos, forks, thd);
	return (0);
}
