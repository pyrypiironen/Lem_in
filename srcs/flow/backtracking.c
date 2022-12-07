#include "../../includes/lem_in.h"



int		check_duplicate_path(lem_data *d, t_room **route)
{
	int	i;
	int	j;

	i = 0;
	while (i < d->path_index)
	{
		j = 1;
		while (d->paths[i][j] != d->end || route[j] != d->end)
		{
			if (d->paths[i][j] != route[j])
			{
				break ;
			}
				
			j++;
		}
		if (d->paths[i][j] == d->end && route[j] == d->end)
		{
			return (1);
		}
		i++;
	}
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
	while (route[j] != d->end)
		j++;
	j++;
	d->paths[d->path_index] = (t_room **)malloc(sizeof(t_room) * j);
	if (d->paths[d->path_index] == NULL)
		exit(1);
	if (d->path_index < 10000)
		d->step_array[d->path_index] = j - 1;
	while (i < j)
	{
		d->current = route[i];
		
		d->paths[d->path_index][i] = route[i];
		i++;
	}
	update_pipe_flow(d);
	d->path_index += 1;
	if (d->path_index == d->path_mem)
		dynamic_path_mem(d);
}

void	backtrack(lem_data *d, t_room *room, int i)
{
	int	pipe_index;

	pipe_index = 0;
	while (pipe_index < room->pipe_count)
	{
		d->route[i] = room;
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

