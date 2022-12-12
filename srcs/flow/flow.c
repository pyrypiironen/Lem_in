/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjokela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:37:54 by mjokela           #+#    #+#             */
/*   Updated: 2022/11/24 13:37:57 by mjokela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	solve_flow(lem_data *d)
{
	init_data(d);
	init_routes(d);
	get_floors(d);
	if (d->end->floor == -1)
		print_error();
	get_unique(d);
	find_best(d);
}

void	flow_routes(lem_data *d)
{
	int		i;
	t_room	*room;

	i = 0;
	while (i < d->room_count)
		d->hashmap[i++]->used = 0;
	while (1)
	{
		init_bfs(d);
		i = d->room_count - 1;
		room = d->end;
		while (!d->stop_bfs)
			bfs(d);
		backtrack(d, room, i);
		if (d->stop_backtrack == 1)
			break ;
		cleanup(d);
	}
	sort_paths(d);
}

void	sort_paths(lem_data *d)
{
	int	max;
	int	current;
	int	i;

	max = 0;
	i = 0;
	current = d->step_array[0];
	d->sorted_paths = (t_room ***)malloc(sizeof(t_room **) * d->path_index + 1);
	if (d->sorted_paths == NULL)
		exit(1);
	while (i < d->path_index)
	{
		if (d->step_array[i] > max)
			max = d->step_array[i];
		i++;
	}
	overwrite_sorted(d, current, max);
	overwrite_paths(d);
}

void	add_to_empty(lem_data *d, t_room *from, t_room *to, int flow)
{
	int	i;

	i = 0;
	from->pipe_flow[flow] = 2;
	d->bfs_rooms[d->bfs_index] = to->r_index;
	while (to->pipes[i]->r_index != from->r_index)
		i++;
	to->pipe_flow[i] = 1;
	d->bfs_index += 1;
}

void	against_flow(lem_data *d, t_room *from, t_room *to, int flow)
{
	int	i;

	i = 0;
	from->pipe_flow[flow] = 3;
	d->bfs_rooms[d->bfs_index] = to->r_index;
	while (to->pipes[i]->r_index != from->r_index)
		i++;
	to->pipe_flow[i] = 3;
	d->bfs_index += 1;
}
