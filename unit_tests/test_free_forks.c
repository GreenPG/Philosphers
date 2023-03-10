/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free_forks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpasquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 09:39:23 by gpasquet          #+#    #+#             */
/*   Updated: 2023/02/25 14:08:50 by gpasquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../greatest/greatest.h"
#include <philo.h>

///////////////////////////////////////////////////////////////////////////////
/// ASSERTIONS

///////////////////////////////////////////////////////////////////////////////
///	TESTS

TEST	simple_input(void)	{
	t_forks	*f1 = init_forks("4");
	t_forks	*f2 = init_forks ("-1");

	free_forks(&f1);
	ASSERT_EQ_FMT(NULL, f1, "%p");
	free_forks(&f2);
	ASSERT_EQ_FMT(NULL, f2, "%p");
	PASS();
}	

///////////////////////////////////////////////////////////////////////////////
///	SUITE

SUITE(free_forks_suite)	{
	RUN_TEST(simple_input);
}
