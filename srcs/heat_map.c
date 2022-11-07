


#include "../../includes/lem_in.h"


int	check_heat_map(lem_data *d, int nb, int in)
{
	while (1)
	{
		while (!compare_array(d, nb, in))
		{
			nb++;
			if (in == 0 && nb >= d->array[d->routes_cur->route_count - 1])
				return (1);
			if (nb == d->path_index) //ei loytynyt ei-konfliktaavaa reittia
			{
				d->rec_counter += 1;
				return (0);
			}
		}
		d->array[in] = nb;
		update_current_steps(d, in);
		
		sleep(1);
		if (d->current_steps >= d->total_steps)
			return (0);
		if (in + 1 == d->routes_cur->route_count && d->current_steps < d->total_steps)
			fill_route_array(d);
		if (nb + 1  == d->path_index)
			return (1); // Tässä haluttas palauttaa 2 => lem_dataan jotain tietoa ja palautus solution_found
		if (check_heat_map(d, nb + 1, in + 1) != 0)
			return (1);
		nb++;
	}
	return (-1);
}