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
		{
			get_move_counts(d);
			
			if (d->routes_cur->move_count < d->best_moves)
				d->best_moves = d->routes_cur->move_count;
			if (d->routes_cur->route_count == d->path_limit)
				break ;
			d->routes_cur = d->routes_cur->next;
			d->rec_counter = 0;
		}
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

void	init_unique_recursive(lem_data *d)
{
	int	i;

	i = 0;
	d->path_depth = d->end->floor;
	d->path_index = 0;
	d->heat_map_index = 0;
	d->best_moves = 2147483647;
	while (i < 10000)
		d->array[i++] = 2147483647;
	d->rec_paths = (t_room ***)malloc(sizeof(t_room **) * d->path_mem);
	if (d->rec_paths == NULL)
		exit(1);
}

int	find_more_routes(lem_data *d)
{
	t_room	**route;
	t_room	*room;
	int		ret;

	room = d->end;
	d->current = d->end;
	route = (t_room **)malloc(sizeof(t_room) * d->path_depth);
	if (route == NULL)
		exit(1);
	ret = recursive_finder(d, route, room, d->path_depth);
	d->path_depth += 1;
	free(route);
	return (ret);
	
}

int	recursive_finder(lem_data *d, t_room **route, t_room *room, int steps)
{
	int	pipe_index;

	pipe_index = 0;
	if (d->rec_counter++ > 30000000)
	{
		
		return (3);
	}
	while (pipe_index < room->pipe_count)
	{
		route[steps] = room;
		if (room == d->start && steps == 0)
			return (save_path_recursive(d, route));
		if (\
		(route[steps] == d->end || route[steps + 1] != room->pipes[pipe_index]))
		{
			steps--;
			if (steps >= 0)
			{
				room->used = 1;
				if (room->pipes[pipe_index]->used != 1)
					if (recursive_finder(d, route, room->pipes[pipe_index], steps) == 3)
						return (3);
				room->used = -1;
			}
			steps++;
		}
		pipe_index++;
	}
	return (1);
}

int	save_path_recursive(lem_data *d, t_room **route)
{
	int	i;

	i = 0;
	d->rec_paths[d->path_index] = (t_room **)malloc(sizeof(t_room) * d->path_depth);
	if (d->rec_paths[d->path_index] == NULL)
		exit(1);
	if (d->path_index < 10000)
		d->step_array[d->path_index] = d->path_depth;
	while (i <= d->path_depth)
	{
		d->rec_paths[d->path_index][i] = route[i];
		i++;
	}
	d->path_index += 1;
	if (d->path_index == d->path_mem)
		dynamic_path_mem_recursive(d);
	return (0);
}

void	dynamic_path_mem_recursive(lem_data *d)
{
	t_room	***tmp;
	int		i;

	i = d->path_index - 1;
	tmp = d->rec_paths;
	d->path_mem += d->path_mem;
	d->rec_paths = (t_room ***)malloc(sizeof(t_room **) * d->path_mem);
	if (d->rec_paths == NULL)
		exit(1);
	while (i >= 0)
	{
		d->rec_paths[i] = tmp[i];
		i--;
	}
	free(tmp);
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
	while (d->rec_paths[d->heat_map_index][j] != d->end)
	{
		k = 1;
		while (d->rec_paths[i][k] != d->end)
		{
			if (d->rec_paths[d->heat_map_index][j] == d->rec_paths[i][k])
				return (1);
			k++;
		}
		j++;
	}
	return (0);
}