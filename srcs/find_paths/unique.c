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
	int		ret;

	d->path_depth = d->end->floor;
	d->path_index = 0;
	d->heat_map_index = 0;
	int	i = 0;
	while (i < 10000)
		d->array[i++] = 2147483647;
	d->paths = (t_room ***)malloc(sizeof(t_room **) * d->path_mem);
	if (d->paths == NULL)
		exit(1);

	// return 1 = taso löytyi | return 2 = haetaan lisää reittejä

	while (1)
	{	
		ret = solution_found(d);
		//ft_printf("{green}ret: %d", ret);

		if (ret == 1)
		{
			if (d->routes_cur->route_count == d->path_limit)
				break ;
			d->routes_cur = d->routes_cur->next;
			d->total_steps = 2147483647;

		}
		if (d->routes_cur->route_count == 12) // HARD CODED
		{
			d->path_limit = d->max_route_count;
			break ;
		}
			
			

		// Täällä tason korotus, jos palautus 1 ja tsekki, onko lopullinen ratkaisu
		room = d->end;
		d->current = d->end;
		route = (t_room **)malloc(sizeof(t_room) * d->path_depth);
		if (route == NULL)
			exit(1);
		// Pitäiskö recursive finder tehdä tämän loopin ulkopuolella, niin ei aloiteta aina alusta
		recursive_finder(d, route, room, d->path_depth);
		d->path_depth += 1;
		if (d->rec_counter > 1000000)
		{
			d->path_limit = d->max_route_count;
			break ;
		}
		//ft_printf("rec_counter %i\n", d->rec_counter);
		free(route);
	}
}




void	recursive_finder(lem_data *d, t_room **route, t_room *room, int steps)
{
	int	pipe_index;

	pipe_index = 0;
	
	while (pipe_index < room->pipe_count)
	{
		//d->rec_counter += 1;
		route[steps] = room;
		if (room == d->start && steps == 0) 
		{
			save_path(d, route);
			return ;
		}
		// room->floor >= room->pipes[pipe_index]->floor && 
		if (\
		(route[steps] == d->end || route[steps + 1] != room->pipes[pipe_index]))
		{
			steps--;
			if (steps >= 0)
				recursive_finder(d, route, room->pipes[pipe_index], steps);
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
	ft_printf("route_count: %d\n", d->routes_cur->route_count);
	while (i < d->routes_cur->route_count)
	{
		d->routes_cur->arr[i] = d->array[i];
		i++;
	}
	int k = 0;
	while (k < d->routes_cur->route_count)
	{
		ft_printf("{yellow}%i [%d]\n", d->routes_cur->arr[k], d->step_array[d->routes_cur->arr[k]]);
		k++;
	}
	// if (d->routes_cur->route_count != d->path_limit)
	// 	d->routes_cur = d->routes_cur->next;

		
	d->total_steps = d->current_steps;
}

void	init_routes(lem_data *d)
{
	int		i;

	i = 1;
	d->total_steps = 2147483647;
	d->routes_cur = (routes *)malloc(sizeof(routes));
	if (d->routes_cur == NULL)
		exit (1);
	d->routes_head = d->routes_cur;
	d->routes_cur->route_count = 1;
	while (i < d->path_limit)
	{
		d->routes_cur->next = (routes *)malloc(sizeof(routes));
		if (d->routes_cur->next == NULL)
			exit (1);
		d->routes_cur = d->routes_cur->next;
		d->routes_cur->route_count = i + 1;
		i++;
	}
	d->routes_cur = d->routes_head;
}

int	compare_array(lem_data *d, int nb, int in)
{
	int	i;

	//ft_printf("{green}Compare array | nb is %i | in = %i\n", nb, in);
	i = 0;
	while (i < in)
	{
		if (d->heat_map[nb][d->array[i]] != 0)
		{
			//ft_printf("Compare array return is 0.\n");
			return (0);
		}
		i++;
	}
	//ft_printf("Compare array return is 1.\n");
	return (1);
}