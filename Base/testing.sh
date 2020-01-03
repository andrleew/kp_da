#! /bin/bash

g++ AnsTest.cpp -O3 -march='native' -o ansTest
g++ genTest.cpp -O3 -march='native' -o genTest
make

for ((i=1; i > 0; i++))
do
    echo $i $i
    for ((j=1; j < i; j++))
    do
        echo $i $i | ./genTest > file
        ./ansTest < file > f1
        ./Base < file > f2
        diff -q f1 f2 > /dev/null
        if [ $? -ne 0 ]
        then
            exit 0
        fi
    done
done
