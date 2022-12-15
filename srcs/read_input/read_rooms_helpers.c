/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjokela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:22:52 by mjokela           #+#    #+#             */
/*   Updated: 2022/11/17 14:22:56 by mjokela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

int	is_room(lem_data *d, char *room)
{
	d->current = d->head;
	while (d->current)
	{
		if (ft_strcmp(d->current->name, room) == 0)
			return (1);
		d->current = d->current->next;
	}
	return (0);
}

int	is_valid(lem_data *d)
{
	int	i;

	i = 0;
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
	return (1);
}

void	create_room(lem_data *d)
{
	int	i;

	i = 0;
	if (d->line[0] == 'L' || ft_strchr(d->line, '-') != NULL)
		print_error();
	init_current(d);
	while (d->line[i] != ' ')
	{
		if (i == 200)
			print_error();
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
	d->current->r_index = d->room_count;
	d->room_count += 1;
}

void	init_current(lem_data *d)
{
	if (d->head != NULL)
	{
		d->current->next = (t_room *)malloc(sizeof(t_room));
		d->current = d->current->next;
	}
	else
		d->current = (t_room *)malloc(sizeof(t_room));
	if (d->current == NULL)
		exit(1);
	d->current->pipe_count = 0;
	d->current->ant_nbr = 0;
	d->current->pipe_mem = ARRAY_SIZE;
	d->current->floor = -1;
	d->current->used = -1;
	if (d->head == NULL)
		d->head = d->current;
}

int	lem_atoi(const char *str)
{
	unsigned long int	res;
	int					sign;

	res = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (unsigned long int)*str - '0';
		if (res > 2147483648 && sign < 0)
			print_error();
		if (res > 2147483647 && sign > 0)
			print_error();
		str++;
	}
	if (*str != ' ' && *str != '\n' && *str != '\0')
		print_error();
	return (sign * (int)res);
}
