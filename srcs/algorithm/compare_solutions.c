/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_solutions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjokela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:40:33 by mjokela           #+#    #+#             */
/*   Updated: 2022/11/17 16:40:38 by mjokela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	find_best(lem_data *d)
{
	d->routes_head->move_count = 2147483647;
	d->routes_cur = d->routes_head;
	while (1)
	{
		get_move_counts(d);
		if (d->routes_cur->move_count < d->routes_best->move_count)
			d->routes_best = d->routes_cur;
		if (d->routes_cur->route_count >= d->path_limit)
			break ;

		d->routes_cur = d->routes_cur->next;
	}
	
}

void	get_move_counts(lem_data *d)
{
	int	ants;
	int	i;
	int	value_array[10000];

	i = -1;
	ants = d->ants;
	while (++i < d->routes_cur->route_count)
		value_array[i] = d->step_array[d->routes_cur->arr[i]];
	while (ants > 0)
	{
		i = d->routes_cur->route_count - 1;
		while (value_array[i - 1] <= value_array[i] && i >= 1)
			i--;
		value_array[i] += 1;
		ants--;
	}
	i = 0;
	d->routes_cur->move_count = value_array[d->routes_cur->route_count - 1] - 1;
	while (i < d->routes_cur->route_count)
	{
		if (value_array[i] - 1 > d->routes_cur->move_count)
			d->routes_cur->move_count = value_array[i] - 1;
		i++;
	}
}
