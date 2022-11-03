

#include "../includes/lem_in.h"

void	send_ants(lem_data *d)
{
	int	ants;
	t_room	***best_paths;
	int		*best_steps;
	int	i;

	ants = d->ants;
	i = 0;
	d->start->ant_nbr = 1;
	d->best_route_count = d->routes_best->route_count;
	best_paths = (t_room ***)malloc(sizeof(t_room **) * d->routes_best->route_count);
	best_steps = (int *)malloc(sizeof(int) * d->routes_best->route_count);
	if (best_paths == NULL || best_steps == NULL)
		exit (1);
	while (i < d->routes_best->route_count)
	{
		best_paths[i] = d->paths[d->routes_best->arr[i]];
		best_steps[i] = d->step_array[d->routes_best->arr[i]];
		i++;
	}
	// for (int i = 0; i < d->routes_best->route_count; i++)
	// {
	// 	ft_printf("{red}route: %d, steps: %d\n", i, best_steps[i]);
	// 	for (int j = 0; ft_strcmp(best_paths[i][j]->name,  d->end->name) != 0; j++)
	// 	{
	// 		ft_printf("%s\n", best_paths[i][j]->name);
	// 	}
	// }
	while (d->end->ant_nbr < ants)
		move_ants(d, best_paths, best_steps);

}



void	move_ants(lem_data *d, t_room ***best_paths, int *best_steps)
{
	int	i;
	int	j;


	i = 0;
	d->space = 0;
	while (i < d->best_route_count)
	{
		
		//sleep(1);
		j = best_steps[i] - 1;
		
		ft_printf("{red}loop");
		while (j >= 0)
		{
			//ft_printf("name: %s, ant_count %d\n", best_paths[i][j]->name, best_paths[i][j]->ant_nbr);
			if (best_paths[i][j]->ant_nbr != 0)
			{
				move_ant(d, best_steps, best_paths, i, j);
				
		
				
				//break ;
			}
			j--;
		}
		i++;
		// if (i < d->routes_best->route_count)
		// 	ft_printf(" ");
	}
	//sleep(1);
	// ft_printf("{red}i: %i, j: %d", i, j);
	ft_printf("{yellow}|moves: %d", d->routes_best->move_count);
	//ft_printf("{green}i: %d, routes: %d", i, d->routes_best->route_count);
	ft_printf("\n");
	

	
	d->routes_best->move_count -= 1;
	while (d->routes_best->move_count < best_steps[d->routes_best->route_count - 1])
		d->routes_best->route_count -= 1;
	// if (d->routes_best->route_count == 0)
	// 	d->routes_best->route_count = 1;
}

void	move_ant(lem_data *d, int *best_steps, t_room ***best_paths, int i, int j)
{

	if (i >= d->routes_best->route_count && j == 0)
		return ;
	if (j + 1 == best_steps[i])
		d->end->ant_nbr += 1;
	else
		best_paths[i][j + 1]->ant_nbr = best_paths[i][j]->ant_nbr;
	if (j != 0)
		best_paths[i][j]->ant_nbr = 0;
	else if (d->start->ant_nbr == d->ants)
		d->start->ant_nbr = 0;
	else
		d->start->ant_nbr += 1;
	if (d->space)
		ft_printf(" ");
	d->space = 1;
	ft_printf("L%d-%s", best_paths[i][j + 1]->ant_nbr, best_paths[i][j + 1]->name);
	//sleep(1);
	// if (i + 1 <= d->best_route_count && best_paths[i][j]->ant_nbr != 0)
	// 	ft_printf(" ");
}