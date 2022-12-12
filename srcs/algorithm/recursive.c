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

	init_unique_recursive(d);
	while (1)
	{	
		ret = solution_found_recursive(d);
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
		dynamic_path_mem_recursive(d);
	return (0);
}

int	solution_found_recursive(lem_data *d)
{
	if (d->path_index == 0)
		return (0);
	fill_heat_map_recursive(d);
	return (check_heat_map(d, 0, 0));
}

void	fill_heat_map_recursive(lem_data *d)
{
	int	i;

	while (d->path_index >= d->map_size)
		dynamic_heat_map(d);
	while (d->heat_map_index < d->path_index)
	{
		i = 0;
		while (i < d->heat_map_index)
		{
			d->heat_map[d->heat_map_index][i] = is_conflict_recursive(d, i);
			i++;
		}
		d->heat_map_index += 1;
	}
}

int	is_conflict_recursive(lem_data *d, int i)
{
	int	j;
	int	k;

	j = 1;
	while (d->paths[d->heat_map_index][j] != d->end)
	{
		k = 1;
		while (d->paths[i][k] != d->end)
		{
			if (d->paths[d->heat_map_index][j] == d->paths[i][k])
				return (1);
			k++;
		}
		j++;
	}
	return (0);
}
