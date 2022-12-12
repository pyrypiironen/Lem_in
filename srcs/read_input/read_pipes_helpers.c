/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pipes_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjokela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:39:35 by mjokela           #+#    #+#             */
/*   Updated: 2022/11/17 14:39:38 by mjokela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	read_pipes(lem_data *d)
{
	while (1)
	{
		lem_to_print(d);
		free(d->line);
		if (get_next_line(0, &d->line) == 0 || skip_comments(d) == -1)
			break ;
		if (!is_pipe(d))
			print_error();
	}
}

int	is_pipe(lem_data *d)
{
	char	first[200];
	char	second[200];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (d->line[i] != '-' && i < 200)
	{
		first[i] = d->line[i];
		if (first[i] == ' ' || first[i++] == '\0')
			return (0);
	}
	first[i++] = '\0';
	while (d->line[i] && j < 200)
	{
		second[j] = d->line[i++];
		if (second[j++] == ' ')
			return (0);
	}
	second[j] = '\0';
	if (is_room(d, first) && is_room(d, second))
		return (create_pipe(d, first, second));
	return (0);
}

int	create_pipe(lem_data *d, char *first, char *second)
{
	t_room	*room;

	room = d->head;
	d->current = d->head;
	while (ft_strcmp(d->current->name, first) != 0)
		d->current = d->current->next;
	while (ft_strcmp(room->name, second) != 0)
		room = room->next;
	add_pipe(d->current, room);
	add_pipe(room, d->current);
	return (1);
}

void	add_pipe(t_room *src, t_room *dst)
{	
	if (dst->pipe_count == 0)
	{
		dst->pipes = (t_room **)malloc(sizeof(t_room *) * dst->pipe_mem);
		if (dst->pipes == NULL)
			exit(1);
	}
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
	if (dst->pipes == NULL)
		exit(1);
	while (i >= 0)
	{
		dst->pipes[i] = tmp[i];
		i--;
	}
	free(tmp);
}
