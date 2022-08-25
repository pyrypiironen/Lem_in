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
		get_next_line(0, &d->line);
		skip_comments(d);
		create_room(d);	// Maybe should ask is_valid first.
		d->start = d->current;
		ret = 1;
	}
	else if (ft_strcmp(d->line, "##end") == 0)
	{
		free(d->line);
		get_next_line(0, &d->line);
		skip_comments(d);
		create_room(d);	// Maybe should ask is_valid first.
		d->end = d->current;
		ret = 1;
	}
	return (ret);
}

int		is_pipe(lem_data *d)
{
	char	first[42];
	char	second[42];
	int		i;
	int		j;

	ft_printf("is_pipe\n");
	ft_printf("line is: %s\n", d->line);
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
	if (is_room(d, first) && is_room(d, second))
		return (1);
	return (0);
}

int		is_room(lem_data *d, char *room)
{
	d->current = d->start;
	while (d->current)
	{
		if (ft_strcmp(d->current->name, room) == 0)
			return (1);
		d->current = d->current->next;
	}
	return (0);
}

int		is_valid(lem_data *d)
{
	int	i;

	ft_printf("is_valid\n");
	//ft_printf("line is: %s\n", d->line);
	i = 0;
	skip_comments(d);
	while (d->line[i++] != ' ')
		if (d->line == '\0')
			return (0);
	i++;
	while (d->line[i] != ' ')
	{
		if (d->line[i] < '0' || d->line[i] > '9')
			return (0);
		i++;
	}
	i++;
	while (d->line[i] != '\0')
	{
		if (d->line[i] < '0' || d->line[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	create_room(lem_data *d)
{
	int i;
	ft_printf("create_room\n");
	// d->head yms pitää alustaa nulleiksi, kun lem_data luodaan.
	i = 0;
	// If head is null, there is not a single room, and new room will be created
	// to d->current and is the head. Else new room will be created to
	//	d->current->next. After this function, d->current is last created room.
	if (d->head != NULL)
		d->current = d->current->next;
	d->current = (t_room *)malloc(sizeof(t_room));
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
	// Nyt menee läpi myö rivit, jossa on ylimääräistä tavaraa koordinaattien
	// perässä. Luo error check.
}
