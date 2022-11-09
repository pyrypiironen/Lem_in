#clear
gcc -Wall -Wextra -Werror -g srcs/*.c srcs/*/*.c libft/libft.a
#leaks -atExit -- ./a.out < test.txt
#clear
./a.out < maps/generator_maps/gen_superposition_2