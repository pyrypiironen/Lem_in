# * * * * * * * * * * TEST AUGMENTS * * * * * * * * * *
echo "Test all augment maps from ./maps/cases/"
echo ""
for f in ./maps/cases/*
do
	echo ""
	echo "NEXT ONE: $f"
	../lem-in -t < $f
done



# # * * * * * * * * * * TEST AUGMENTS without flags: * * * * * * * * * *
# echo "Test all augment maps from ./maps/cases/"
# echo ""
# for f in ./maps/cases/*
# do
# 	echo ""
# 	echo "NEXT ONE: $f"
# 	../lem-in < $f
# done



# echo ""
# echo "Augment 1"
# echo ""
#  ../lem-in < ./maps/cases/augment_1.map