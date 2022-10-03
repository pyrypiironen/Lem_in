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
	t_room	**route;
	t_room	*room;



	d->path_depth = d->end->floor;
	d->path_index = 0;
	d->heat_map_index = 0;
	d->paths = (t_room ***)malloc(sizeof(t_room **) * PATH_COUNT); // make this dynamic
	// check mallocs
	
	while (!solution_found(d))
	{
		room = d->end;
		d->current = d->end;
		route = (t_room **)malloc(sizeof(t_room) * d->path_depth);
		// check malloc
		recursive_finder(d, route, room, d->path_depth);
		d->path_depth += 1;
		free(route);
		if (d->path_depth == 42)
			break ;
	}


	// Tarkista, onko tarpeeksi uniikkeja
	// Jos ei, niin seuraava leveli
}

int		solution_found(lem_data *d)
{
	if (d->path_index == 0)
		return (0);
	// Lue nykyinen taso heat_mappiin.
	fill_heat_map(d);
	// Tarkista löytyikö ratkaisu
	int r;
	r = check_heat_map(d, 0, 0);
	ft_printf("{purple}check_heat_map return is = %d\n", r);
	//sleep(10);
	return (0);
}

void	fill_heat_map(lem_data *d)
{
	int	i;

	while (d->heat_map_index < d->path_index)
	{
		i = 0;
		while (i < d->heat_map_index)
		{
			d->heat_map[d->heat_map_index][i] = is_conflict(d, i);
			i++;
		}
		d->heat_map_index += 1;
	}

	ft_printf("path_index: %d\n", d->path_index);
	for (int k = 0; k < 20; k++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (d->heat_map[k][j] == 2)
				ft_printf(" %d ", d->heat_map[k][j]);
			else if (d->heat_map[k][j] == 0)
				ft_printf("{green} %d ", d->heat_map[k][j]);
			else
				ft_printf("{red} %d ", d->heat_map[k][j]);
		}
			
		ft_printf("\n");
	}
}

int		is_conflict(lem_data *d, int i)
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


void	recursive_finder(lem_data *d, t_room **route, t_room *room, int steps)
{
	int	pipe_index;

	pipe_index = 0;
	while (pipe_index < room->pipe_count)
	{
		route[steps] = room;
		if (room == d->start && steps == 0) 
		{
			save_path(d, route);
			return ;
		}
		
		if (room->floor >= room->pipes[pipe_index]->floor && (route[steps] == d->end || route[steps + 1] != room->pipes[pipe_index]))
		{
			steps--;
			if (steps >= 0)
				recursive_finder(d, route, room->pipes[pipe_index], steps);
			steps++;
		}
		pipe_index++;
	}
}

int	check_heat_map(lem_data *d, int nb, int in) // Eka kutsu in = 0; nb 0;
{
	while (1)
	{
		while (!compare_array(d, nb, in))
		{
			nb++;
			//ft_printf("{purple}path_index = %i\n", d->path_index);
			//sleep(5);
			if (nb == d->path_index)
			{	
				ft_printf("{red} return check_heat_map (0)\n");
				return (0);
			}
		}
		d->array[in] = nb;
		if (in + 1 == d->path_limit)
		{
			int k = 0;
			while (k < d->path_limit)
			{
				ft_printf("{yellow}%i \n", d->array[k]);
				k++;
			}
			return (1);
		}
		if (nb + 1  == d->path_index)
		{	
			ft_printf("{yellow} return check_heat_map (0)\n");
			return (0);
		}
		if (check_heat_map(d, nb + 1, in + 1) == 1)
			return (1);
		nb++;

	}
	return (-1);
}

int	compare_array(lem_data *d, int nb, int in)
{
	int	i;

	ft_printf("{green}compare array | nb is %i | in = %i\n", nb, in);
	i = 0;
	while (i < in)
	{
		if (d->heat_map[nb][d->array[i]] != 0)
		{
			ft_printf("compare array retunr is 0\n");
			return (0);
		}
		i++;
	}
	ft_printf("compare array retunr is 1\n");
	return (1);
}