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
	d->stop_bfs = 0;
	d->bfs_copy[0] = d->start->r_index;
	d->bfs_copy[1] = -1;
	// while (i < d->start->pipe_count)
	// {
	// 	d->bfs_copy[i] = d->start->pipes[i]->r_index;
	// 	i++;
	// }
	// d->bfs_copy[i] = -1;
	while (!d->stop_bfs)
		bfs(d);
	for (int i = 0; i < d->room_count; i++)
	{
		ft_printf("{green}room: %s (%d)\n", d->hashmap[i]->name, d->hashmap[i]->r_index);
		for (int j = 0; j < d->hashmap[i]->pipe_count; j++)
		{
			ft_printf("{yellow}pipes: %s %i\n", d->hashmap[i]->pipes[j]->name, d->hashmap[i]->pipe_flow[j]);
		}
	}
	exit(1);
}

void	bfs(lem_data *d)
{
	int	i;
	int	j;

	i = 0;
	while (d->bfs_copy[i] != -1)
	{
		j = 0;

		while (j < d->hashmap[d->bfs_copy[i]]->pipe_count) // Korjaa niin, että aloitetaan aina startista, vaikka ei olis eka huone (vai onko tehty)
		{
			if (d->hashmap[d->bfs_copy[i]]->r_index != d->end->r_index)
				arrows(d, d->hashmap[d->bfs_copy[i]], d->hashmap[d->bfs_copy[i]]->pipes[j], j);
			// ft_printf("{green}room: %s\n", d->hashmap[i]->name);
			// ft_printf("{yellow}pipes: %s %i\n", d->hashmap[i]->pipes[j]->name, d->hashmap[i]->pipes[j]->pipe_flow[j]);
			// sleep(1);
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
		from->parent == to->r_index)
		return ;
	to->parent = from->r_index;
	if (from->pipe_flow[flow] == 0)
		add_to_empty(d, from, to, flow);
	else // On 1, vastakkainen nuoli
		against_flow(d, from, to, flow);

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
	if (to->r_index == d->end->r_index)
		d->stop_bfs = 1;
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

void	copy_bfs(lem_data *d)
{
	int	i;

	i = 0;
	while (d->bfs_rooms[i] != -1)
	{
		d->bfs_copy[i] = d->bfs_rooms[i];
		i++;
	}
	d->bfs_copy[i] = -1;
}