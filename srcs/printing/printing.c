/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjokela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:33:21 by mjokela           #+#    #+#             */
/*   Updated: 2022/11/17 14:33:28 by mjokela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lem_in.h"

void	print_error(void)
{
	ft_printf("ERROR\n");
	exit(1);
}

void	lem_to_print(lem_data *d)
{
	lem_print	*new;

	new = (lem_print *)malloc(sizeof(lem_print));
	if (new == NULL)
		exit(1);
	new->str = ft_strdup(d->line);
	new->next = NULL;
	if (d->print_head == NULL)
	{
		d->print_head = new;
		d->print_current = d->print_head;
	}
	else
	{
		d->print_current->next = new;
		d->print_current = d->print_current->next;
	}
}

void	print_super_solution(lem_data *d)
{
	int	i;

	i = 1;
	while (i <= d->ants)
	{
		ft_printf("L%d-%s", i, d->end->name);
		if (i < d->ants)
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
	exit(0);
}

void	print_input(lem_data *d)
{
	while (d->print_head != NULL)
	{
		ft_printf("%s\n", d->print_head->str);
		d->print_head = d->print_head->next;
	}
	ft_printf("\n");
}
