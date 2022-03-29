echo "Compiling gen.cpp"
g++ gen.cpp -std=c++17 -o gen
echo "Compiling ac.cpp"
g++ ac.cpp -std=c++17 -o ac
# make ac
echo "Compiling main.cpp"
g++ main.cpp -std=c++17 -o main

((count = 0))
((testCases = 1000))
for((i = 1; ; i++)); do
	echo "Running on test ${i}"
	
	# generate input
	./gen $i > test
	
	# generate correct output
	./ac < test > out1
	
	# test python solution main.py 
	# python main.py < test > out1
	
	#test cpp solution main.cpp
	./main < test > out2

	# print "Ok" if code finished successfully (no RTE)
	# break otherwise
	if [ $? -eq 0 ]
	then
		echo "Ok"
	else
		echo "RTE"
		break
	fi

	# break if outputs are different
	diff -w out1 out2 || break
	((count++))
done

if [ $count -eq $testCases ]
then
	echo "Accepted"
else
	((count++))
	echo "Wrong Answer on test ${count}"
	cat test
	echo "Answer : "
	cat out1
	echo "Output : "
	cat out2
fi
