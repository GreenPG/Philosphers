/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:18:19 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/14 16:59:45 by gpasquet         ###   ########.fr       */
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
	death_dt->t_die = philos[0]->t_die;
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

static void	death_end(t_death *death_dt, int philo_id, long int current_time)
{
	int	i;

	pthread_mutex_lock(&death_dt->philos[philo_id]->ph_mut);
	death_dt->philos[philo_id]->state = dead;
	change_status(dead, death_dt->philos[philo_id], current_time);
	pthread_mutex_unlock(&death_dt->philos[philo_id]->ph_mut);
	i = 0;
	while (i < death_dt->nb_philo)
	{
		if (i != philo_id)
		{
			pthread_mutex_lock(&death_dt->philos[philo_id]->ph_mut);
			/* printf("HERE\n"); */
			death_dt->philos[philo_id]->end_mark = 1;
			pthread_mutex_unlock(&death_dt->philos[philo_id]->ph_mut);
		}
		i++;
	}
}

void	*death(void	*data)
{
	t_death		*death_dt;
	int			i;
	long int	current_time;

	death_dt = data;
	while (1)
	{
		i = 0;
		while (i < death_dt->nb_philo)
		{
			current_time = get_set_time(2);
			if (death_dt->philos[i]->finish == 1)
				death_dt->finished_ph++;
			if (current_time - death_dt->philos[i]->last_eat_t >= death_dt->t_die)
			{	
				/* printf("Philo %i:\ncurrent time: %li\nlast time eat :%li\ntime to die : %li\n", i + 1, current_time, death_dt->philos[0]->last_eat_t, death_dt->t_die); */
				death_end(death_dt, i, current_time);
				exit(0);
			}
			i++;
		}
		if (death_dt->finished_ph == death_dt->nb_philo)
		{
			eat_end(death_dt);
			exit(0);
		}
		death_dt->finished_ph = 0;
	}
}
