#clear
gcc -Wall -Wextra -Werror srcs/*.c libft/libft.a
#leaks -atExit -- ./a.out < test.txt
#clear
./a.out < test.txt
rm a.out