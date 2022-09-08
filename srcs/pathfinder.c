

//HEADER

#include "../includes/lem_in.h"

void	solve_paths(lem_data *d)
{
	d->path_limit = d->start->pipe_count;
	if (d->end->pipe_count < d->path_limit)
		d->path_limit = d->end->pipe_count;
	if (d->path_limit > d->ants)
		d->path_limit = d->ants;
	get_floors(d);
	get_unique(d);
	// Etsi parhaat reitit


}

void	get_unique(lem_data *d)
{
	t_room	**route;
	t_room	*room;


	d->path_depth = d->end->floor;
	d->path_index = 0;
	d->paths = (t_room ***)malloc(sizeof(t_room **) * PATH_COUNT); // make this dynamic
	d->unique_paths = (t_room ***)malloc(sizeof(t_room **) * d->path_limit);
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
	}


	// Tarkista, onko tarpeeksi uniikkeja
	// Jos ei, niin seuraava leveli
}


int		solution_found(lem_data *d)
{
	if (d->path_index < d->path_limit)
		return (0);
	return (unicorn_finder(d, 0));
}

int		unicorn_finder(lem_data	*d, int	level)
{
	int	i;
	int	j;

	i = 0;
	ft_printf("%d\n", level);
	if (level== 0)
	{
		d->unique_paths[0] = d->paths[0];
		d->unique_index = 1;
		if (unicorn_finder(d, 1))
			return (1);
	}
	while (i < d->unique_index) //verrataan kasilla olevaa reittia kaikkiin
								//aikaisempiin
	{
		j = level;
		while (j < d->path_index)
		{
			if (is_conflict(d, i, j))
			{
				j++;
				i = 0;
			}
			else
			{
				if (i + 1 == d->unique_index)
				{
					d->unique_paths[d->unique_index] = d->paths[j];
					if (d->unique_index == d->path_limit)
						return (1);
				}
				else if (unicorn_finder(d, level + 1))
						return (1);
				break ;
			}
		}
		i++;
	}
	d->unique_index++;
	return (0);
}

int		is_conflict(lem_data *d, int i, int j)
{
	ft_printf("seg here\n");
	int	k;
	int	m;

	k = 1;
	while (d->unique_paths[i][k] != d->end)
	{
		m = 1;
		while (d->paths[j][m] != d->end)
		{
			if (d->unique_paths[i][k] == d->paths[j][m])
				return (1);
			m++;
		}
		k++;
	}
	ft_printf("or seg here\n");
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

void	save_path(lem_data *d, t_room **route)
{
	int	i;

	i = 0;
	d->paths[d->path_index] = (t_room **)malloc(sizeof(t_room) * d->path_depth);
	// malloc check

	while (i <= d->path_depth)
	{
		d->paths[d->path_index][i] = route[i];
		i++;
	}
	d->path_index += 1; // tarkista tarviiko dynaamisesti allokoida tilaa
}

void	get_floors(lem_data *d)
{
	int	new;
	int	level;
	int	i;

	new = 1;
	level = 0;
	d->start->floor = 0;
	while (new)
	{
		d->current = d->head;
		new = 0;
		while (d->current->next != NULL)
		{
			if (d->current->floor == level)
			{
				i = 0;
				while (i < d->current->pipe_count)
				{
					if (d->current->pipes[i]->floor == -1)
					{
						d->current->pipes[i]->floor = level + 1;
						new = 1;
					}
					i++;
				}
			}
			d->current = d->current->next;
		}
		level++;
	}
}