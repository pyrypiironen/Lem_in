

#include "../../includes/lem_in.h"

int		is_pipe(lem_data *d)
{
	char	first[42];
	char	second[42];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (d->line[i] != '-')
	{
		first[i] = d->line[i];
		if (first[i] == ' ' || first[i++] == '\0')
			return (0);
	}
	first[i] = '\0';
	i++;
	while (d->line[i])
	{
		second[j] = d->line[i++];
		if (second[j++] == ' ')
			return (0);
	}
	second[j] = '\0';
	if (is_room(d, first) && is_room(d, second))
	{
		create_pipe(d, first, second);
		return (1);
	}
	return (0);
}

void	create_pipe(lem_data *d, char *first, char *second)
{
	t_room *room;

	room = d->head;
	d->current = d->head;

	while (ft_strcmp(d->current->name, first) != 0)
		d->current = d->current->next;
	while (ft_strcmp(room->name, second) != 0)
		room = room->next;
	add_pipe(d, d->current, room);
	add_pipe(d, room, d->current);
}

void	add_pipe(lem_data *d, t_room *src, t_room *dst)
{	
	(void)d; /////
	//t_room **tmp;

	if (dst->pipe_count == 0)
		dst->pipes = (t_room **)malloc(sizeof(t_room *) * dst->pipe_mem);
	else if (dst->pipe_count == dst->pipe_mem)
		dynamic_array(dst);
	dst->pipes[dst->pipe_count] = src;
	dst->pipe_count++;
}

void	dynamic_array(t_room *dst)
{
	t_room	**tmp;
	int		i;

	i = dst->pipe_mem - 1;
	tmp = dst->pipes;
	dst->pipe_mem += ARRAY_SIZE;
	dst->pipes = (t_room **)malloc(sizeof(t_room *) * dst->pipe_mem);
	// add malloc check
	while (i >= 0)
	{
		dst->pipes[i] = tmp[i];
		i--;
	}
	free(tmp);
}