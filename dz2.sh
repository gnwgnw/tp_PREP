#!/bin/bash

make -f dz2.make
echo "run gen_inp_file.py"
python3 ./gen_inp_file.py

echo "TEST BASE MATRIX"
./dz2.out base_matrix.txt
echo "##############################################"

cnt=0
LIMIT=10
file=""
while [ "$cnt" -lt "$LIMIT" ]
do
	file="$file square_matrix$cnt.txt" 
	#echo "$file" 
	cnt=$((cnt+1))
done

echo "TEST GOOG SQUARE MATRIX"
./dz2.out$file
echo "##############################################"

cnt=0
LIMIT=10
file=""
while [ "$cnt" -lt "$LIMIT" ]
do
        file="$file rectangle_matrix$cnt.txt"
        #echo "$file" 
        cnt=$((cnt+1))
done

echo "TEST GOOG RECTANGLE  MATRIX"
./dz2.out$file
echo "##############################################"

echo "TEST ZERO INPUT PARAMS"
./dz2.out zero_inp_matrix.txt
echo "##############################################"

echo "TEST WTF INPUT NUMBERS"
./dz2.out WTF_matrix.txt

echo "TEST LITTLE DATA"
./dz2.out little_data_matrix.txt
echo "##############################################"

echo "TEST REPEAT INPUT INDEX"
./dz2.out repeat_data_matrix.txt
echo "##############################################"

echo "TEST OVERLOAD INTEGER"
./dz2.out overload_int.txt
echo "##############################################"

rm -f *.txt
rm -f *.o
