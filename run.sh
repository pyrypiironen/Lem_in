#clear
gcc -Wall -Wextra -Werror srcs/*.c libft/libft.a
#leaks -atExit -- 
#clear
./a.out < test.txt
rm a.out