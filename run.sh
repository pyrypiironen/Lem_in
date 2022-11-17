#clear
gcc -Wall -Wextra -Werror srcs/*.c srcs/*/*.c libft/libft.a
#leaks -atExit -- ./a.out < test.txt
#clear
./a.out -m < maps/generator_maps/map_big_sup_10

#./lem-in -m < maps/generator_maps/map_big_sup_10