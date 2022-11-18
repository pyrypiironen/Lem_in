
#leaks -atExit -- ./a.out < test.txt
make re
clear
leaks --atExit -- ./lem-in < maps/other_maps/zero_ants
make clean
#./lem-in -m < maps/generator_maps/map_big_sup_10