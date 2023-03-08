/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:25:36 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/08 12:55:05 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <pthread.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			ret;
	int			sign;

	i = 0;
	ret = 0;
	sign = 1;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		ret = (ret * 10) + (nptr[i] - 48);
		i++;
	}
	ret *= sign;
	return (ret);
}

long long	get_set_time(int par, t_philo *ph_data)
{
	struct timeval			tmval;
	static struct timeval	start_time;
	long long	time;

	(void)ph_data;
	if (par <= 1)
	{
		if (par == 0)
			gettimeofday(&start_time, NULL);
		return (0);
	}
	gettimeofday(&tmval, NULL);
	time = (tmval.tv_sec - start_time.tv_sec) * 1000 + (tmval.tv_usec - start_time.tv_usec) / 1000;
	return (time);
}
