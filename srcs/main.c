/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:27:46 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/10 15:14:15 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*start_thd(void	*data)
{
	t_philo			*ph_data;
	long int		current_time;
	long int		last_eat_t;

	ph_data = data;
	current_time = get_set_time(2, ph_data);
	last_eat_t = current_time;
	life_loop(ph_data, current_time, last_eat_t);
	return (0);
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
