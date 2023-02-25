/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 09:39:23 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/25 11:29:03 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include <philo.h>

///////////////////////////////////////////////////////////////////////////////
/// ASSERTIONS

///////////////////////////////////////////////////////////////////////////////
///	TESTS

TEST	simple_input(void)	{
	t_forks	*f1 = malloc(sizeof(t_forks));
	t_forks	*f2 = malloc(sizeof(t_forks));
	t_forks	*f3 = malloc(sizeof(t_forks));
	f1->philo_nb = 4;
	f1->tab = malloc(sizeof(int) * 4);
	for	(int i = 0; i < 4; i++)
		f1->tab[i] = 0;
	f2->philo_nb = -1;
	f1->philo_nb = 4;

	free_forks(&f1);
	ASSERT_EQ_FMT(NULL, f1, "%p");
	free_forks(&f2);
	ASSERT_EQ_FMT(NULL, f2, "%p");
	free_forks(&f3);
	ASSERT_EQ_FMT(NULL, f3, "%p");
	PASS();
}	

///////////////////////////////////////////////////////////////////////////////
///	SUITE

SUITE(free_forks_suite)	{
	RUN_TEST(simple_input);
}
