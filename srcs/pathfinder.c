

//HEADER

#include "../includes/lem_in.h"

void	solve_paths(lem_data *d)
{
	d->path_limit = d->start->pipe_count;
	if (d->end->pipe_count < d->path_limit)
		d->path_limit = d->end->pipe_count;
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
	
	while (solution_found())
	{
		room = d->end;
		d->current = d->end;
		route = (t_room **)malloc(sizeof(t_room) * d->path_depth);
		recursive_finder(d, route, room, d->path_depth);
		d->path_depth += 1;
		free(route);
	}


	// Tarkista, onko tarpeeksi uniikkeja
	// Jos ei, niin seuraava leveli
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
			// ft_printf("{red}routes:\n");
			// ft_printf("route index 0: %s\n", route[0]->name); //tallenna reitti
			// ft_printf("route index 1: %s\n", route[1]->name); //tallenna reitti
			// ft_printf("route index 2: %s\n", route[2]->name); //tallenna reitti
			// ft_printf("route index 3: %s\n", route[3]->name); //tallenna reitti
			// ft_printf("route index 4: %s\n", route[4]->name); //tallenna reitti
			return ;
		}
		if (room->floor >= room->pipes[pipe_index]->floor && (route[steps] == d->end || route[steps + 1] != room->pipes[pipe_index]))
		{
			//room = room->pipes[pipe_index];
			steps--;
			if (steps >= 0)
			{
				//d->current = room;
				recursive_finder(d, route, room->pipes[pipe_index], steps);
			}
				
			steps++;
		}
		//d->current = room;
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