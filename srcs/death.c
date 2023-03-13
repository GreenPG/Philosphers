/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:18:19 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/13 17:02:09 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_death	*init_death(t_philo **philos, int nb_philos)
{
	t_death	*death_dt;

	death_dt = malloc(sizeof(t_death));
	if (!death_dt)
		return (NULL);
	death_dt->nb_philo = nb_philos;
	death_dt->t_die = 0;
	death_dt->finished_ph = 0;
	death_dt->philos = philos;
	return (death_dt);
}

static void	eat_end(t_death *death_dt)
{
	int	i;

	i = 0;
	while (i < death_dt->nb_philo)
	{
		pthread_mutex_lock(&death_dt->philos[i]->ph_mut);
		death_dt->philos[i]->end_mark = 1;
		pthread_mutex_unlock(&death_dt->philos[i]->ph_mut);
		i++;
	}
}

void	*death(void	*data)
{
	t_death		*death_dt;
	int			i;

	death_dt = data;
	while (1)
	{
		i = 0;
		while (i < death_dt->nb_philo)
		{
			pthread_mutex_lock(&death_dt->philos[i]->ph_mut);
			if (death_dt->philos[i]->finish == 1)
				death_dt->finished_ph++;
			i++;
		}
		if (death_dt->finished_ph == death_dt->nb_philo)
		{
			pthread_mutex_unlock(&death_dt->philos[i]->ph_mut);
			eat_end(death_dt);
			exit(0);
		}
		pthread_mutex_lock(&death_dt->philos[i]->ph_mut);
		death_dt->finished_ph = 0;
	}
}
