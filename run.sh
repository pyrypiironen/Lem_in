
#leaks -atExit -- ./a.out < test.txt
make re
make clean
clear
time ./lem-in -m < maps/generator_maps/gen_big_0
#time ./lem-in -m < maps/generator_maps/map_big_sup_1
#time ./lem-in -m < mini_gauntlet/cases/augment_8.map