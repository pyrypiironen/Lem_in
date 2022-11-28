#include "../../includes/lem_in.h"

int	backtrack(lem_data *d)
{
	int		i;
	int		j;
	t_room	**route;
	int apu = 0;

	i = d->room_count;
	d->current = d->end;
	d->path_depth = 0;
	route = (t_room **)malloc(sizeof(t_room) * d->room_count + 1);
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
		d->path_depth += 1;
		if (d->current->r_index == 16)
		{
			ft_printf("{purple}o reitille\n");
			apu = 1;
			//sleep(1);
		}
		if (apu)
			ft_printf("{purple}huone: %s\n", d->current->name);
		route[i--] = d->current;
		d->current= update_pipe_flow(d, j);
	}
	save_path(d, &route[i]);
	free(route);
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

