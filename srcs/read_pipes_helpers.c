

#include "../includes/lem_in.h"

void	create_pipe(lem_data *d, char *first, char *second)
{

	t_room *room;


	room = d->head;
	d->current = d->head;
	ft_printf("create_pipe\n");
	while (ft_strcmp(d->current->name, first) != 0)
		d->current = d->current->next;
	while (ft_strcmp(room->name, second) != 0)
		room = room->next;
	add_pipe(d, d->current, room);
	//add_pipe(d, room, d->current);
	ft_printf("create pipe end\n");


}

void	add_pipe(lem_data *d, t_room *src, t_room *dst)
{
	ft_printf("täs\n");
	(void)d;
	dst->pipes[dst->pipe_count] = (t_room *)malloc(sizeof(t_room));
	ft_printf("täs\n");
	// add malloc check;
	dst->pipes[dst->pipe_count] = src;
	ft_printf("täs\n");
	//dst->pipe_count++;
}

void	create_room(lem_data *d)
{
	int		i;
	//t_room	*tmp;

	ft_printf("create_room\n");
	// d->head yms pitää alustaa nulleiksi, kun lem_data luodaan.
	i = 0;
	// If head is null, there is not a single room, and new room will be created
	// to d->current and is the head. Else new room will be created to
	//	d->current->next. After this function, d->current is last created room.
	if (d->head != NULL)
	{
		d->current->next = (t_room *)malloc(sizeof(t_room));
		d->current = d->current->next;
	}
	else
		d->current = (t_room *)malloc(sizeof(t_room));
	d->current->pipes = (t_room **)malloc(sizeof(t_room *));
	// add malloc checks
	d->current->pipe_count = 0;
	if (d->head == NULL)
		d->head = d->current;
	// Save the name and coordinates to node s_room.
	while (d->line[i] != ' ')
	{
		d->current->name[i] = d->line[i];
		i++;
	}
	d->current->name[i] = '\0';
	d->current->x = lem_atoi(&d->line[i + 1]);
	i++;
	while (d->line[i] != ' ')
		i++;
	d->current->y = lem_atoi(&d->line[i + 1]);
	d->current->next = NULL;
	// Nyt menee läpi myö rivit, jossa on ylimääräistä tavaraa koordinaattien
	// perässä. Luo error check.
}