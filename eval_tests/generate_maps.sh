rm -rf maps/big_sup
mkdir maps/big_sup
rm -rf maps/big
mkdir maps/big
rm -rf maps/flow
mkdir maps/flow
for i in {1..20}
do
	./generator --big-superposition > maps/big_sup/$i.sup
	./generator --big > maps/big/$i.big
	./generator --flow-one > maps/flow/$i.one
	./generator --flow-ten > maps/flow/$i.ten
	./generator --flow-thousand > maps/flow/$i.thousand
	sleep .4
done
