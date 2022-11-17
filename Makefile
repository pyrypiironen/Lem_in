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

FILES = *.c



all: $(LEMIN)

$(LEMIN): $(OBJS) $(LIBFT)
		@gcc $(FLAGS) -o $@ $^
		@echo "Lem-in succesfully done."

$(LIBFT):
		@$(MAKE) -C libft

clean:
		@rm -f $(OBJS)
		@$(MAKE) -C libft clean

fclean: clean
		@rm f- $(LEMIN)
		@$(MAKE) -C libft fclean
		@echo "Make fclean succesfully done."

re: fclean all

.PHONY: all clean fclean re
