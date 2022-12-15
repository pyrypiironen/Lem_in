# * * * * * * * * * * TEST ERRORS * * * * * * * * * *
echo "Test all error maps from ./maps/error_maps/"
echo ""
for f in ./maps/error/*
do
	../lem-in < $f
done