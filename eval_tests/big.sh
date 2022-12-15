for f in ./maps/big/*
do
	time ../lem-in -s < $f
done
