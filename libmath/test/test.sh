#!/bin/bash

# list all of the test files of the folder set
test_src=( test_matrix.h test_scalar.h test_wiseOp.h test_exception.h test_vector.h ) 
# list of all the test files to test. Default is all the args.
test_files=( $@ )

# Handle case when there is no arguments
if [ "$1" == "" ] 
then
	test_files=${test_src[@]:0} ;
fi

# Test if file exist
for i in ${test_files[@]}
do
	if ! test -e $i
	then
		echo "!!!File $i does not exist!!!";
		test_files=( "${test_files[@]/$i}" )
	fi
done 

# Test files if there is some remaining
if [ "${test_files[@]}" == "" ]
then
	echo "No file to test.";
else
	# Use cxxtest to run tests
	../../cxxtest-4.4/bin/cxxtestgen --error-printer -o runner.cpp  ${test_files[@]:0}
# 	nvcc -o runner -I ../inc -I ../../cxxtest-4.4 runner.cpp ../src/Matrix.cu -std=c++11
	g++ -o runner -I ../inc -I ../../cxxtest-4.4 runner.cpp -std=c++11
	./runner
	rm runner
	rm runner.cpp
fi
