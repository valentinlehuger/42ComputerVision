#!/bin/bash

# list all of the test files of the folder set
test_src=( test_dbi.h ) 
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
	../../cxxtest-4.4/bin/cxxtestgen --error-printer -o runner.cpp ${test_files[@]:0}
	g++ ../srcs/csvReader.cpp  ../../libimg/srcs/img_decompress.cpp -o runner -I ../../libcv/inc -I ../inc -I ../../cxxtest-4.4  -I../../CImg-1.6.3/ -I../../libmath/inc/ -I../../libimg/inc/ -I ../../libcv/inc/NN.hpp runner.cpp -std=c++11 -O2 -lm -lpthread -I ~/.brew/Cellar/boost/1.58.0/include/ -I ~/42cv_repo/mongodb/mongo-cxx-driver/build/install/include -pthread -L ~/42cv_repo/mongodb/mongo-cxx-driver/build/install/lib -lmongoclient -Dcimg_display=0 -Dcimg_use_png -L ~/.brew/lib -L ~/.brew/Cellar/boost/1.58.0/lib/ -I ~/.brew/Cellar/libpng/1.6.17/include/ -L ~/.brew/Cellar/libpng/1.6.17/lib/ -lpng -lboost_thread-mt -lboost_system -lboost_regex
	./runner
	rm runner
	rm runner.cpp
fi
