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

# define ARRAY_SIZE	42
# define PATH_COUNT	42

typedef struct	s_room
{
	char		name[42]; // Ei voi olla pointteri, jos ei allokoida tilaa erikseen.
	int			x;
	int			y;
	struct		s_room	*next;
	struct		s_room	**pipes;
	int			pipe_count;
	int			pipe_mem;
	int			floor;
}				t_room;

typedef struct	lem_data
{
	struct	s_room	*head;
	struct	s_room	*current; // Added
	struct	s_room	*start;
	struct	s_room	*end;
	int		ants;
	int		path_limit;
	char	*line;				// Added
	struct	s_room	***paths;
	int		path_index;
	int		path_depth;
}			lem_data;


// Read input
void	input(lem_data *d);
void	read_ants(lem_data *d);
void	read_rooms(lem_data *d);
void	read_pipes(lem_data *d);
int		skip_comments(lem_data *d);

// Read rooms helpers
int		check_start_end(lem_data *d);
int		is_pipe(lem_data *d);
int		is_room(lem_data *d, char *room);
int		is_valid(lem_data *d);
void	create_room(lem_data *d);

// Read pipes helpers
void	create_pipe(lem_data *d, char *first, char *second);
void	add_pipe(lem_data *d, t_room *src, t_room *dst);
void	dynamic_array(t_room *dst);

// Helpers
int		lem_atoi(const char *str);

// Solving paths
void	solve_paths(lem_data *d);
void	get_floors(lem_data *d);
void	get_unique(lem_data *d);
void	recursive_finder(lem_data *d, t_room **route, t_room *room, int steps);
void	save_path(lem_data *d, t_room **route);




#endif
