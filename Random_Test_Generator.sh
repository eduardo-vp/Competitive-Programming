# Gracias men de la uni

echo "Compiling gen.cpp"
g++ gen.cpp -std=c++14 -o gen
echo "Compiling ac.cpp"
g++ ac.cpp -std=c++14 -o ac
echo "Compiling main.cpp"
g++ main.cpp -std=c++14 -o main

((count = 0))
((testCases = 1000))
for((i = 1; ; i++)); do
	echo "Running on test ${i}"
	./gen $i > test
	./ac < test > out1
	./main < test > out2
	diff -w out1 out2 || break
	((count++))
done

if [ $count -eq $testCases ]
then
	echo "Accepted"
else
	((count++))
	echo "Wrong Answer on test ${count}"
	more test
	echo "Answer : "
	more out1
	echo "Output : "
	more out2
fi
