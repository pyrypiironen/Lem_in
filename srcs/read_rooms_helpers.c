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
	ft_printf("d->current is %s\n", d->current->name);
	ft_printf("first: %s, is_room: %d\n", first, is_room(d, first));
	ft_printf("second: %s, is_room: %d\n", second, is_room(d, second));
	ft_printf("is pipe return is 0\n");				// HOX!
	return (0);
}

int		is_room(lem_data *d, char *room)
{
	d->current = d->head;
	while (d->current)
	{
	//ft_printf("d->current is %s\n", d->current->name);
	//ft_printf("room is %s\n", room);
		if (ft_strcmp(d->current->name, room) == 0)
			return (1);
		ft_printf("d->current is %s\n", d->current->name);
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
		if (d->line[i - 1] == '\0')
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
	//ft_printf("valid return is 1 here\n");
	return (1);
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
	//d->current->pipes = (t_room **)malloc(sizeof(t_room *));
	// add malloc checks
	d->current->pipe_count = 0;
	d->current->pipe_mem = ARRAY_SIZE;
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