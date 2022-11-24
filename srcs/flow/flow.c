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

void	flow_routes(lem_data *d)
{
	int	i;

	i = 0;
	d->bfs_index = 0;
	d->bfs_rooms[0] = -1;
	while (i < d->start->pipe_count)
	{
		d->bfs_copy[i] = d->start->pipes[i]->r_index;
		i++;
	}
	d->bfs_copy[i] = -1;
}

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
			arrows(d, d->bfs_copy[i], d->hashmap[d->bfs_copy[i]]->pipes[j], j);
			j++;
		}
		i++;
	}
}

void	arrows(lem_data *d, t_room *from, t_room *to, int flow)
{
	if (from->pipe_flow[flow] == (2 || 3)) // ONKO OIKEIN?
		return ;
	else if (from->pipe_flow[flow] == 0)
		add_to_empty(d, from, to, flow);
	else // On 1, vastakkainen nuoli
		;

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
}

