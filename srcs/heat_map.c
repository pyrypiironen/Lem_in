


#include "../includes/lem_in.h"


int	check_heat_map(lem_data *d, int nb, int in)
{
	int	ret;

	while (1)
	{
		while (!compare_array(d, nb, in))
		{
			nb++;
			// if (in == 0 && nb >= d->array[d->routes_cur->route_count - 1])
			// 	return (1);
			if (nb == d->path_index) //ei loytynyt ei-konfliktaavaa reittia
			{
				d->rec_counter += 1;
				return (0);
			}
		}
		//ft_printf("in: %d, nb: %d\n", in, nb);
		d->array[in] = nb;
		update_current_steps(d, in);
		//ft_printf("cur: %d, total: %d\n", d->current_steps, d->total_steps);
		//sleep(1);
		if (d->current_steps >= d->total_steps)
			return (0);
		if (in + 1 == d->routes_cur->route_count && d->current_steps < d->total_steps)
		{
			fill_route_array(d);
			if (in == 0 && nb >= d->array[d->routes_cur->route_count - 1])
				return (1);
			return (0);
		}
			
		//ft_printf("cur: %d, total: %d\n", d->current_steps, d->total_steps);
	//	ft_printf("vika tallennettu: %d\n", d->array[d->routes_cur->route_count - 1]);
		if (in == 0 && nb >= d->array[d->routes_cur->route_count - 1])
			return (1);
		//ft_printf("nb: %d, steps: %d\n", nb, d->step_array[nb]);
		if (nb + 1 == d->path_index)
			return (2); // Tässä haluttas palauttaa 2 => lem_dataan jotain tietoa ja palautus solution_found
		//ft_printf("nb + 1: %d, in + 1: %d, path_index: %d\n", nb + 1, in + 1, d->path_index);
		if (d->current_steps + d->step_array[nb + 1] >= d->total_steps || nb > d->array[d->routes_cur->route_count - 1])
			return (0);
		ret = check_heat_map(d, nb + 1, in + 1);
		
		if (ret != 0)
			return (ret);
		// while (d->step_array[d->array[in]] == d->step_array[nb])
		// {
			if (nb + 1 == d->path_index)
				return (2);
			nb++;
		// }
			

	}
	return (-1);
}