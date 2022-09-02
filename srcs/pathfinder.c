

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
	d->paths = (t_room ***)malloc(sizeof(t_room **) * PATH_COUNT);
	d->path_index = 0;
	// Kaikki pathit per tutkittava steps, eka steps == end->floor
	// Aloitetaan endistä, tutkitaan sama floor ja sitä pienemmät, pysähdytään jos steps menee yli
	// Allokoidaan aina step countin kokoinen tuplapointteri, kirjoitetaan reittiä aina indeksiin, ylikirjoitetaan, jos reitti ei valid
	// Rekursiivinen funktio
	// Tarkista, onko tarpeeksi uniikkeja
	// Jos ei, niin seuraava leveli
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