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
	int		path_stop;

	init_unique(d);
	flow_routes(d);
	path_stop = d->path_index;
	d->path_index = 0;
	while (1)
	{	
		ret = solution_found(d);
		if (compare_moves(d, ret) == 1)
			break ;
		if (ret == 2 || ret == 0)
		{
			d->path_index += 1;
			if (d->path_index - 1 == path_stop)
			{
				d->path_limit = d->routes_cur->route_count - 1;
				break ;
			}
		}
	}
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

int	recursive_finder(lem_data *d, t_room **rou, t_room *room, int steps)
{
	int	pipe;

	pipe = 0;
	if (d->rec_counter++ > 30000000)
		return (3);
	while (pipe < room->pipe_count)
	{
		rou[steps] = room;
		if (room == d->start && steps == 0)
			return (save_path_recursive(d, rou));
		if ((rou[steps] == d->end || rou[steps + 1] != room->pipes[pipe]))
		{
			if (--steps >= 0)
			{
				room->used = 1;
				if (room->pipes[pipe]->used != 1)
					if (recursive_finder(d, rou, room->pipes[pipe], steps) == 3)
						return (3);
				room->used = -1;
			}
			steps++;
		}
		pipe++;
	}
	return (1);
}
