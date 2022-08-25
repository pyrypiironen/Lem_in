// Add header


#include "../includes/lem_in.h"

int		check_start_end(lem_data *d)
{
	int	ret;

	ret = 0;
	// If line is "##start", get_next_line and save it to d->start;
	if (ft_strcmp(d->line, "##start") == 0)
	{
		free(d->line);
		get_next_line(0, d->line);
		skip_comments(d);
		create_room(*d, d->line);	// Maybe should ask is_valid first.
		d->start = d->current;
		ret = 1;
	}
	else if (ft_strcmp(line, "##end") == 0)
	{
		free(d->line);
		get_next_line(0, d->line);
		skip_comments(d);
		create_room(*d, d->line);	// Maybe should ask is_valid first.
		d->end = d->current;
		ret = 1;
	}
	return (ret);
}

int		is_pipe(lem_data *d)
{
	char[42]	first;
	char[42]	second;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (d->line[i] != '-')
	{
		first[i] = d->line[i];
		if (first[i] == ' ' || first[i++] == '\0')
			return (0);
	}
	i++;
	while (d->line[i])
	{
		second[j] = d->line[i++];
		if (second[j++] == ' ')
			return (0);
	}
	if (is_room(d, first) && is_room(d, second)
		return (1);
	return (0);
}

int		is_room(lem_data *d, char *room)
{
	d->current = d->start;
	while (d->current)
	{
		if (ft_strcmp(d->current, room) == 0)
			return (1);
		d->current = d->current->next;
	}
	return (0);
}

int		is_valid(lem_data *d, muuta?)
{
	
}

void	create_room(lem_data *d, char *str)
{
	int i;
	// d->head yms pitää alustaa nulleiksi, kun lem_data luodaan.

	// If head is null, there is not a single room, and new room will be created
	// to d->current and is the head. Else new room will be created to
	//	d->current->next. After this function, d->current is last created room.
	if (d->head != NULL)
		d->current = d->current->next;
	d->current = (s_room *)malloc(sizeof(s_room));
	if (d->head == NULL)
		d->head = d->current;
	// Save the name and coordinates to node s_room.
	while (str[i] != ' ')
		d->current->name[i] = str[i++];
	d->current->name[i] = '\0';
	d->current->x = lem_atoi(str[i + 1]);
	i++;
	while (str[i] != ' ')
		i++;
	d->current->y = lem_atoi(str[i + 1]);
	// Nyt menee läpi myö rivit, jossa on ylimääräistä tavaraa koordinaattien
	// perässä. Luo error check.
}


