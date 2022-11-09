


#include "../includes/lem_in.h"


// int	check_heat_map_big(lem_data *d, int nb, int in)
// {

// }

int	check_heat_map(lem_data *d, int nb, int in)
{
	int	ret;

	d->rec_counter += 1;
	//find_more_routes(d);
	// sleep(1);
	if (d->rec_counter > 3000000)
		return (3);
	while (1)
	{
		while (!compare_array(d, nb, in))
		{
			nb++;
			if (nb == d->path_index) //ei loytynyt ei-konfliktaavaa reittia
			{
				//d->rec_counter += 1;
				return (0);
			}
		}
		d->array[in] = nb;
		// update_current_steps(d, in);
		// if (d->current_steps >= d->total_steps)
		// 	return (0);
		if (in + 1 == d->routes_cur->route_count && d->current_steps < d->total_steps)
		{
			fill_route_array(d);
			return (1); // Testi palautetaan eka tulos
			if ((in == 0 && nb >= d->array[d->routes_cur->route_count - 1]) || d->routes_cur->route_count > 8)
				return (1);
			return (0);
		}
		if (in == 0 && nb >= d->array[d->routes_cur->route_count - 1])
			return (1);
		if (nb + 1 == d->path_index)
			return (2); 
		if (d->current_steps + d->step_array[nb + 1] >= d->total_steps || nb > d->array[d->routes_cur->route_count - 1])
		{
			if (nb == 0)
				return (1);
			return (0);
		}
		ret = check_heat_map(d, nb + 1, in + 1);
		if (ret != 0)
			return (ret);
		nb++;
	}
	return (-1);
}