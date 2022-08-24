/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:50:28 by ppiirone          #+#    #+#             */
/*   Updated: 2022/08/21 14:50:29 by ppiirone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

typedef struct	s_room
{
	char[42]	name; // Ei voi olla pointteri, jos ei allokoida tilaa erikseen.
	int			x;
	int			y;
	struct		s_room	*next;
	struct		s_room	**tubes;
	int			t_count;
}				t_room;

typedef struct	lem_data
{
	struct	s_room	*head;
	struct	s_room	*current; // Added
	struct	s_room	*start;
	struct	s_room	*end;
	int		ants;
	char	*line;				// Added
}			lem_data;


// Read input
void	input(lem_data *d);
void	read_ants(lem_data *d);

// Helpers
int		lem_atoi(const char *str);




#endif
