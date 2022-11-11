#clear
gcc -Wall -Wextra -Werror -g srcs/*.c srcs/*/*.c libft/libft.a
#leaks -atExit -- ./a.out < test.txt
#clear
./a.out < mini_gauntlet/cases/augment_8.map