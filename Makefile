# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppiirone <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 14:23:45 by ppiirone          #+#    #+#              #
#    Updated: 2022/11/17 14:23:46 by ppiirone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEMIN = lem-in
FLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a

MAIN = 			main.c

ALGO_FILES =	compare_solutions.c \
				heat_map.c \
				send_ants.c \
				recursive.c

PATH_FILES =	helpers.c \
				pathfinder.c \
				solution_found.c \
				unique.c

PRINT_FILES =	printing.c

INPUT_FILES =	checking.c \
				read_input.c \
				read_pipes_helpers.c \
				read_rooms_helpers.c

FLOW_FILES =	flow.c \
				backtracking.c \
				cleanup.c

MAIN_SRCS = $(addprefix srcs/main/, $(MAIN))
ALGO_SRCS = $(addprefix srcs/algorithm/, $(ALGO_FILES))
PATH_SRCS = $(addprefix srcs/find_paths/, $(PATH_FILES))
PRINT_SRCS = $(addprefix srcs/printing/, $(PRINT_FILES))
INPUT_SRCS = $(addprefix srcs/read_input/, $(INPUT_FILES))
FLOW_SRCS = $(addprefix srcs/flow/, $(FLOW_FILES))

SRCS = $(MAIN_SRCS) $(ALGO_SRCS) $(PATH_SRCS) $(PRINT_SRCS) $(INPUT_SRCS) \
$(FLOW_SRCS)

OBJS = $(SRCS:.c=.o)


all: $(LEMIN)

$(LEMIN): $(OBJS) $(LIBFT)
		@gcc $(FLAGS) -o $@ $^
		@echo "Lem-in succesfully done."

$(LIBFT):
		@$(MAKE) -C libft

clean:
		@rm -f $(OBJS)
		@$(MAKE) -C libft clean
		@echo "Make clean succesfully done."

fclean: clean
		@rm -f $(LEMIN)
		@$(MAKE) -C libft fclean
		@echo "Make fclean succesfully done."

re: fclean all

.PHONY: all clean fclean re
