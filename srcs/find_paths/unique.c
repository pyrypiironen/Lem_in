/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:33:09 by ppiirone          #+#    #+#             */
/*   Updated: 2022/09/22 11:33:11 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	get_unique(lem_data *d)
{
	int		ret;

	init_unique(d);
	while (1)
	{	
		ret = solution_found(d);
		if (ret == 1)
		{
			get_move_counts(d);
			if (d->routes_cur->move_count < d->best_moves)
				d->best_moves = d->routes_cur->move_count;
			if (d->routes_cur->route_count == d->path_limit)
				break ;
			d->routes_cur = d->routes_cur->next;
			d->total_steps = 2147483647;
			d->rec_counter = 0;
		}
		if (ret == 3 || d->best_moves <= d->path_depth)
		{
			d->path_limit = d->max_route_count;
			break ;
		}
		if (ret == 2 || ret == 0)
			find_more_routes(d);
	}
}

void	find_more_routes(lem_data *d)
{
	t_room	**route;
	t_room	*room;

	room = d->end;
	d->current = d->end;
	route = (t_room **)malloc(sizeof(t_room) * d->path_depth);
	if (route == NULL)
		exit(1);
	recursive_finder(d, route, room, d->path_depth);
	d->path_depth += 1;
	free(route);
}

void	recursive_finder(lem_data *d, t_room **route, t_room *room, int steps)
{
	int	pipe_index;

	pipe_index = 0;
	while (pipe_index < room->pipe_count)
	{
		route[steps] = room;
		if (room == d->start && steps == 0) 
			return (save_path(d, route));
		if (\
		(route[steps] == d->end || route[steps + 1] != room->pipes[pipe_index]))
		{
			steps--;
			if (steps >= 0)
			{
				room->used = 1;
				if (room->pipes[pipe_index]->used != 1)
					recursive_finder(d, route, room->pipes[pipe_index], steps);
				room->used = -1;
			}
			steps++;
		}
		pipe_index++;
	}
}

void	fill_route_array(lem_data *d)
{
	int	i;

	i = 0;
	d->max_route_count = d->routes_cur->route_count;
	//ft_printf("route_count: %d\n", d->routes_cur->route_count);
	while (i < d->routes_cur->route_count)
	{
		d->routes_cur->arr[i] = d->array[i];
		i++;
	}
	int k = 0;
	while (k < d->routes_cur->route_count)
	{
		//ft_printf("{yellow}%i [%d]\n", d->routes_cur->arr[k], d->step_array[d->routes_cur->arr[k]]);
		k++;
	}
	d->total_steps = d->current_steps;
}

int	compare_array(lem_data *d, int nb, int in)
{
	int	i;

	i = 0;
	while (i < in)
	{
		if (d->heat_map[nb][d->array[i]] != 0)
			return (0);
		i++;
	}
	return (1);
}