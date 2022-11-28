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
	int	j;

	i = 0;
	j = 0;
	init_bfs(d);
	while (!d->stop_bfs)
	{

		bfs(d);
		//d->path_depth += 1;
	}
	
	while (j < d->end->pipe_count)
	{
		if (d->end->pipe_flow[j] == 1)
			backtrack(d);
		j++;
	}
		
	sleep(5);
	for (int i = 0; i < d->path_index; i++)
	{
		for (int j = 0; d->paths[i][j] != d->end; j++)
			ft_printf("{red}%s -> ", d->paths[i][j]->name);
		ft_printf("{red}%s -> ", d->end->name);
		ft_printf("\n");
	}
		
	

	for (int i = 0; i < d->room_count; i++)
	{
		ft_printf("{green}room: %s (%d) a: %d, b: %d\n", d->hashmap[i]->name, d->hashmap[i]->r_index, d->hashmap[i]->parent_a, d->hashmap[i]->parent_b);
		for (int j = 0; j < d->hashmap[i]->pipe_count; j++)
		{
			ft_printf("{yellow}pipes: %s %i\n", d->hashmap[i]->pipes[j]->name, d->hashmap[i]->pipe_flow[j]);
		}
	}
	cleanup(d);
	// // backtrack tähän ja tallennetaan pathseihin, merkkaa 4 ja 5 tallennettuihin reitteihin
	// // Puhdista kartta, jätä 4 ja 5 vai muuta 1 ja 2
	// exit(1);
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
		from->parent_a == to->r_index || from->parent_b == to->r_index || \
		to->used == 2)
		return ;
	if (to->parent_a == -1)
		to->parent_a = from->r_index;
	else
		to->parent_b = from->r_index;
	if (from->pipe_flow[flow] == 0)
		add_to_empty(d, from, to, flow);
	else // On 1, vastakkainen nuoli
		against_flow(d, from, to, flow);
	to->used += 1;
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
	// if (to->r_index == d->end->r_index)
	// 	d->stop_bfs = 1;
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
	if (d->bfs_rooms[0] == -1)
		d->stop_bfs = 1;
	while (d->bfs_rooms[i] != -1)
	{
		d->bfs_copy[i] = d->bfs_rooms[i];
		i++;
	}
	d->bfs_copy[i] = -1;
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
	while (i < d->room_count)
	{
		d->hashmap[i]->used = 0;
		d->hashmap[i]->parent_a = -1;
		d->hashmap[i]->parent_b = -1;
		i++;
	}
}