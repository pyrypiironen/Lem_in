/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjokela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:21:33 by mjokela           #+#    #+#             */
/*   Updated: 2022/12/08 14:21:40 by mjokela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	get_unique_recursive(lem_data *d)
{
	int		ret;

	init_unique(d);
	while (1)
	{	
		ret = solution_found(d);
		if (ret == 1)
			if (compare_moves_recursive(d) == 1)
				break ;
		if (ret == 3 || d->best_moves <= d->path_depth)
		{
			d->path_limit = d->max_route_count;
			break ;
		}
		if (ret == 2 || ret == 0)
		{
			if (find_more_routes(d) == 3)
			{
				d->path_limit = d->max_route_count;
				break ;
			}
		}	
	}
}

int	save_path_recursive(lem_data *d, t_room **route)
{
	int	i;

	i = 0;
	d->paths[d->path_index] = \
		(t_room **)malloc(sizeof(t_room) * d->path_depth);
	if (d->paths[d->path_index] == NULL)
		exit(1);
	if (d->path_index < 10000)
		d->step_array[d->path_index] = d->path_depth;
	while (i <= d->path_depth)
	{
		d->paths[d->path_index][i] = route[i];
		i++;
	}
	d->path_index += 1;
	if (d->path_index == d->path_mem)
		dynamic_path_mem(d);
	return (0);
}

int	compare_moves_recursive(lem_data *d)
{
	get_move_counts(d);
	if (d->routes_cur->move_count < d->best_moves)
		d->best_moves = d->routes_cur->move_count;
	if (d->routes_cur->route_count == d->path_limit)
		return (1);
	d->routes_cur = d->routes_cur->next;
		d->rec_counter = 0;
	return (0);
}
