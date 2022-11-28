#include "../../includes/lem_in.h"

int	backtrack(lem_data *d)
{
	int		i;
	int		j;
	t_room	**route;

	i = d->path_depth;
	d->current = d->end;
	route = (t_room **)malloc(sizeof(t_room) * d->path_depth + 1);
	if (route == NULL)
		print_error();
	while (d->current != d->start)
	{
		j = 0;
		while (d->current->pipe_flow[j] != 1)
		{
			if (j++ == d->current->pipe_count)
			{
				free(route);
				return (1);
			}
		}
		route[i--] = d->current;
		d->current= update_pipe_flow(d, j);
	}
	save_path(d, route);
	return (0);
}

t_room	*update_pipe_flow(lem_data *d, int j)
{
	int	k;

	k = 0;
	d->current->pipe_flow[j] = 4;
	while (d->current->pipes[j]->pipes[k]->r_index != d->current->r_index)
		k++;
	d->current->pipes[j]->pipe_flow[k] = 5;
	return (d->current->pipes[j]);
}

