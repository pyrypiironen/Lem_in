/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:49:02 by ppiirone          #+#    #+#             */
/*   Updated: 2022/12/09 13:49:04 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	bfs(lem_data *d)
{
	int	i;
	int	j;

	i = 0;
	while (d->bfs_copy[i] != -1)
	{
		j = 0;
		while (j < d->hashmap[d->bfs_copy[i]]->pipe_count)
		{
			if (d->hashmap[d->bfs_copy[i]]->r_index != d->end->r_index)
				arrows(d, d->hashmap[d->bfs_copy[i]], \
				d->hashmap[d->bfs_copy[i]]->pipes[j], j);
			j++;
		}
		i++;
	}
	d->bfs_rooms[d->bfs_index] = -1;
	d->bfs_index = 0;
	copy_bfs(d);
}

void	arrows(lem_data *d, t_room *from, t_room *to, int flow)
{
	if (from->pipe_flow[flow] == 2 || from->pipe_flow[flow] == 3 || \
		from->parent_a == to->r_index || from->parent_b == to->r_index || \
		to->used == 1)
		return ;
	if (to->used == 2)
		to->used = -6;
	if (to->parent_a == -1)
		to->parent_a = from->r_index;
	else
		to->parent_b = from->r_index;
	if (from->pipe_flow[flow] == 0)
		add_to_empty(d, from, to, flow);
	else
		against_flow(d, from, to, flow);
	to->used += 1;
}

void	init_bfs(lem_data *d)
{
	int	i;

	i = 0;
	d->bfs_index = 0;
	d->bfs_rooms[0] = -1;
	d->stop_bfs = 0;
	d->bfs_copy[0] = d->start->r_index;
	d->bfs_copy[1] = -1;
	d->path_depth = 0;
	d->stop_backtrack = 1;
	while (i < d->room_count)
	{
		d->hashmap[i]->parent_a = -1;
		d->hashmap[i]->parent_b = -1;
		i++;
	}
}

void	copy_bfs(lem_data *d)
{
	int	i;

	i = 0;
	if (d->bfs_rooms[0] == -1)
		d->stop_bfs = 1;
	while (d->bfs_rooms[i] != -1)
	{
		d->bfs_copy[i] = d->bfs_rooms[i];
		i++;
	}
	d->bfs_copy[i] = -1;
}
