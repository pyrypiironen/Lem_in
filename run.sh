
#leaks -atExit -- ./a.out < test.txt
make re
make clean
#clear
./lem-in -m < maps/generator_maps/map_big_sup_1
#./lem-in -m < mini_gauntlet/cases/augment_8.map