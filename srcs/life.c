/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:27:26 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/14 09:25:40 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	thinking_ph(t_philo *ph_data, long int *current_time,
	long int *last_change_t, long int *last_eat_t)
{
	pthread_mutex_lock(ph_data->forks[0]);
	*current_time = get_set_time(2, ph_data);
	change_status(take, ph_data, *current_time);
	pthread_mutex_lock(ph_data->forks[1]);
	*current_time = get_set_time(2, ph_data);
	*last_change_t = *current_time;
	*last_eat_t = *current_time;
	change_status(take, ph_data, *current_time);
	change_status(eating, ph_data, *current_time);
}

static void	starting_ph(t_philo *ph_data, long int *current_time,
	long int *last_change_t, long int *last_eat_t)
{
	if (ph_data->id % 2 == 0)
	{
		*last_change_t = *current_time;
		pthread_mutex_lock(ph_data->forks[0]);
		*current_time = get_set_time(2, ph_data);
		change_status(take, ph_data, *current_time);
		pthread_mutex_lock(ph_data->forks[1]);
		*current_time = get_set_time(2, ph_data);
		*last_eat_t = *current_time;
		change_status(take, ph_data, *current_time);
		change_status(eating, ph_data, *current_time);
	}
	else
	{
		*last_change_t = *current_time;
		change_status(thinking, ph_data, *current_time);
		usleep(200);
	}
}

static void	eating_ph(t_philo *ph_data, long int *current_time,
	long int *last_change_t, int *eaten_times)
{
	change_status(sleeping, ph_data, *current_time);
	pthread_mutex_unlock(ph_data->forks[0]);
	pthread_mutex_unlock(ph_data->forks[1]);
	*last_change_t = *current_time;
	*eaten_times += 1;
	if (*eaten_times == ph_data->nb_eat)
		ph_data->finish = 1;
}

static void	sleeping_ph(t_philo *ph_data, long int *current_time,
	long int *last_change_t)
{
	*last_change_t = *current_time;
	change_status(thinking, ph_data, *current_time);
}

void	life_loop(t_philo *ph_data, long int current_time,
		long int last_eat_t)
{
	long int		last_change_t;
	int				eaten_times;

	eaten_times = 0;
	while (ph_data->end_mark != 1)
	{
		pthread_mutex_lock(&ph_data->ph_mut);
		current_time = get_set_time(2, ph_data);
		if ((current_time - last_eat_t) > ph_data->t_die)
		{
			change_status(dead, ph_data, current_time);
			break ;
		}
		else if (ph_data->state == thinking)
			thinking_ph(ph_data, &current_time, &last_change_t, &last_eat_t);
		else if (ph_data->state == start)
			starting_ph(ph_data, &current_time, &last_change_t, &last_eat_t);
		else if (ph_data->state == eating && (current_time - last_change_t)
			>= ph_data->t_eat)
			eating_ph(ph_data, &current_time, &last_change_t, &eaten_times);
		else if (ph_data->state == sleeping && (current_time - last_change_t)
			>= ph_data->t_sleep)
			sleeping_ph(ph_data, &current_time, &last_change_t);
		pthread_mutex_unlock(&ph_data->ph_mut);
	}
}
