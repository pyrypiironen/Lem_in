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
	t_room *room;
	// clean up later
	i = 0;
	while (i < d->room_count)
	{
		d->hashmap[i]->used = 0;
		i++;
	}
	//
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
	int	j;
	int	sorted_steps[10000];

	max = 0;
	i = 0;
	j = 0;
	current = d->step_array[0];
	d->sorted_paths = (t_room ***)malloc(sizeof(t_room **) * d->path_index + 1);
	while (i < d->path_index)
	{
		if (d->step_array[i] > max)
			max = d->step_array[i];
		i++;
	}
	while (current <= max)
	{
		i = 0;
		while (i < d->path_index)
		{
			if (d->step_array[i] == current)
			{
				d->sorted_paths[j] = d->paths[i];
				sorted_steps[j] = d->step_array[i];
				j++;
			}
			i++;
		}
		current++;
	}
	i = 0;
	while (i < d->path_index)
	{
		d->paths[i] = d->sorted_paths[i];
		d->step_array[i] = sorted_steps[i];
		i++;
	}	
}

void	print_paths(lem_data *d) //helper, remove
{
	ft_printf("{purple}path_index: %d\n", d->path_index);
	for (int i = 0; i < d->path_index; i++)
		{
			for (int j = 0; d->paths[i][j] != d->end; j++)
				ft_printf("{red}%s -> ", d->paths[i][j]->name);
			ft_printf("{red}%s -> ", d->end->name);
			ft_printf("{yellow} | %d",d->step_array[i]);
			ft_printf("\n");
		}
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
		to->used == 1/* || to->total_used == 2*/)
		return ;
	if (to->used == 2)
		to->used = -6; 															// VARIABLE
	if (to->parent_a == -1)
		to->parent_a = from->r_index;
	else
		to->parent_b = from->r_index;
	if (from->pipe_flow[flow] == 0)
		add_to_empty(d, from, to, flow);
	else // On 1, vastakkainen nuoli
		against_flow(d, from, to, flow);
	to->used += 1;
	//to->total_used += 1;
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
	d->path_depth = 0;
	d->stop_backtrack = 1;
	while (i < d->room_count)
	{
		//d->hashmap[i]->used = 0;
		d->hashmap[i]->parent_a = -1;
		d->hashmap[i]->parent_b = -1;
		i++;
	}
}