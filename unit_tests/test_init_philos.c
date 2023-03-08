/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init_philos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:40:33 by gpasquet          #+#    #+#             */
/*   Updated: 2023/03/08 17:31:11 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <pthread.h>
#include "../greatest/greatest.h"

///////////////////////////////////////////////////////////////////////////////
/// ASSERTIONS

TEST	ASSERT_PHILOS_EQ(t_philo **actual, char **args, t_forks *forks, int size)
{
	int	pos = 0;
	int	ph_nb = atoi(args[0]);

	while (pos < ph_nb)
	{
		ASSERT_EQ_FMT(pos + 1, actual[pos]->id, "%i");
		ASSERT_EQ_FMT(ft_atoi(args[1]), actual[pos]->t_die, "%i");
		ASSERT_EQ_FMT(ft_atoi(args[2]), actual[pos]->t_eat, "%i");
		ASSERT_EQ_FMT(ft_atoi(args[3]), actual[pos]->t_sleep, "%i");
		ASSERT_EQ_FMT(start, actual[pos]->state, "%i");
		if (size == 5)
			ASSERT_EQ_FMT(ft_atoi(args[4]), actual[pos]->nb_eat, "%i");
		if (pos == ph_nb - 1)
		{
			ASSERT_EQ_FMT(&forks->tab[pos], actual[pos]->forks[0], "%p");
			ASSERT_EQ_FMT(&forks->tab[0], actual[pos]->forks[1], "%p");
		}
		else
		{
			ASSERT_EQ_FMT(&forks->tab[pos], actual[pos]->forks[0], "%p");
			ASSERT_EQ_FMT(&forks->tab[pos + 1], actual[pos]->forks[1], "%p");
		}
		pos++;
	}
	free_philos(&actual, ph_nb);
	PASS();
}
///////////////////////////////////////////////////////////////////////////////
///	TESTS

TEST	simple_input(void)
{
	char	*args1[4] = {"4", "323", "3123", "321"};
	char	*args2[5] = {"4", "323", "3123", "321", "43"};
	t_forks	*forks = init_forks("4");

	CHECK_CALL(ASSERT_PHILOS_EQ(init_philos(args1, 4, forks), args1, forks, 4));
	CHECK_CALL(ASSERT_PHILOS_EQ(init_philos(args2, 5, forks), args2, forks, 5));
	free_forks(&forks);
	PASS();
}
///////////////////////////////////////////////////////////////////////////////
///	SUITE

SUITE(init_philos_suite) {
	RUN_TEST(simple_input);
}
