#include "../../includes/lem_in.h"

// void	recursive_finder(lem_data *d, t_room **route, t_room *room, int steps)
// {
// 	int	pipe_index;

// 	pipe_index = 0;
// 	while (pipe_index < room->pipe_count)
// 	{
// 		route[steps] = room;
// 		if (room == d->start && steps == 0)
// 			return (save_path(d, route));
// 		if (\
// 		(route[steps] == d->end || route[steps + 1] != room->pipes[pipe_index]))
// 		{
// 			steps--;
// 			if (steps >= 0)
// 			{
// 				room->used = 1;
// 				if (room->pipes[pipe_index]->used != 1)
// 					recursive_finder(d, route, room->pipes[pipe_index], steps);
// 				room->used = -1;
// 			}
// 			steps++;
// 		}
// 		pipe_index++;
// 	}
// }

int		check_duplicate_path(lem_data *d, t_room **route)
{
	int	i;
	int	j;

	i = 0;
	//sleep(1);
	while (i < d->path_index)
	{
		j = 1;
		while (d->paths[i][j] != d->end || route[j] != d->end)
		{
			//ft_printf("huone 1: %s, huone 2: %s\n", d->paths[i][j]->name, route[j]->name);
			if (d->paths[i][j] != route[j])
			{
				
				break ;
			}
				
			j++;
		}
		if (d->paths[i][j] == d->end && route[j] == d->end)
		{
			//ft_printf("{blue}return 1 check_dupplicates\n");
			return (1);
		}
		i++;
		//ft_printf("loop");
	}
	//sleep(1);
	//ft_printf("{yellow}no loop");
	return (0);
}

void	save_path(lem_data *d, t_room **route)
{
	int	i;
	int	j;


	i = 0;
	j = 0;
	if (d->path_index != 0 && check_duplicate_path(d, route) == 1)
		return ;
	d->stop_backtrack = 0;
	//ft_printf("täs\n");
	while (route[j] != d->end)
		j++;
	j++;
	d->paths[d->path_index] = (t_room **)malloc(sizeof(t_room) * j);
	if (d->paths[d->path_index] == NULL)
		exit(1);
	//ft_printf("path nr. %d\n", d->path_index);
	if (d->path_index < 10000)
		d->step_array[d->path_index] = j - 1;
	while (i < j)
	{
		//ft_printf("täsä\n");
		d->current = route[i];
		
		d->paths[d->path_index][i] = route[i];
		//ft_printf("%d -> ", route[i]->x);
		i++;
	}
	update_pipe_flow(d);
	d->path_index += 1;
	if (d->path_index == d->path_mem)
		dynamic_path_mem(d);
	print_paths(d);
}

void	backtrack(lem_data *d, t_room *room, int i)
{
	int	pipe_index;

	pipe_index = 0;
	while (pipe_index < room->pipe_count)
	{
		d->route[i] = room;
		//ft_printf("laitettu: %s\n", room->name);
		if (room == d->start)
			return (save_path(d, &d->route[i]));
		if (\
		(d->route[i] == d->end || d->route[i + 1] != room->pipes[pipe_index]))
		{
			i--;
			if (room->pipe_flow[pipe_index] == 1 || room->pipe_flow[pipe_index] == 4)
				backtrack(d, room->pipes[pipe_index], i);
			i++;
		}
		pipe_index++;
	}
}

// int	backtrack(lem_data *d)
// {
// 	int		i;
// 	int		j;
// 	t_room	**route;
// 	int apu = 0;

// 	i = d->room_count;
// 	d->current = d->end;
// 	d->path_depth = 0;
// 	route = (t_room **)malloc(sizeof(t_room) * d->room_count + 1);
// 	if (route == NULL)
// 		print_error();
// 	while (d->current != d->start)
// 	{
// 		j = 0;
// 		while (1)
// 		{
// 			if (d->current->pipe_flow[j] == 1)
// 				break ;
// 			else if (d->current->pipe_flow[j] == 4 && d->current != d->end)
// 				break ;
// 			if (j++ == d->current->pipe_count)
// 			{
// 				free(route);
// 				return (1);
// 			}
// 		}
// 		d->path_depth += 1;
// 		if (d->current->r_index == 14)
// 		{
// 			//ft_printf("{purple}m reitille\n");
// 			apu = 1;
// 			//sleep(1);
// 		}
// 		if (apu)
// 			ft_printf("{purple}huone: %s\n", d->current->name);
// 		route[i--] = d->current;
// 		d->current= update_pipe_flow(d, j);
// 	}
// 	save_path(d, &route[i]);
// 	free(route);
// 	return (0);
// }

// t_room	*update_pipe_flow(lem_data *d, int j)
// {
// 	int	k;

// 	k = 0;
// 	d->current->pipe_flow[j] = 4;
// 	while (d->current->pipes[j]->pipes[k]->r_index != d->current->r_index)
// 		k++;
// 	d->current->pipes[j]->pipe_flow[k] = 5;
// 	return (d->current->pipes[j]);
// }

void	update_pipe_flow(lem_data *d)
{
	t_room	**route;
	int		i;
	int		j;

	route = d->paths[d->path_index];
	i = 1;
	d->current = route[0]; 
	while (d->current != d->end)
	{
		j = 0;
		while (d->current->pipes[j] != route[i])
			j++;
		d->current->pipe_flow[j] = 5;
		j = 0;
		while (route[i]->pipes[j] != d->current)
			j++;
		route[i]->pipe_flow[j] = 4;
		d->current = route[i];
		i++;
	}
}

