
#leaks -atExit -- ./a.out < test.txt
make re
make clean
clear
./lem-in -m < maps/generator_maps/gen_big_0
#./lem-in -m < maps/generator_maps/map_big_sup_10