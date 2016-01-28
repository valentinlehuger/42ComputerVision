#
# Makefile
# gbersac, 2015-07-15 14:54
#

INCS :=		../../libcv/inc ../../libmath/inc

all: nn eigen
	mv $(shell pwd)/eigen $(shell pwd)/../eigen && mv $(shell pwd)/nn $(shell pwd)/../nn

nn: 
	g++ src/main_nn.cpp -o nn ../mongodb/srcs/csvReader.cpp  ../libimg/srcs/img_decompress.cpp   -I ../libcv/inc -I ../mongodb/inc  -I ../CImg-1.6.3/ -I ../libmath/inc/ -I ../libimg/inc/ -std=c++11 -O2 -lm -lpthread -I ~/.brew/Cellar/boost/1.58.0/include/ -I ../mongodb/mongo-cxx-driver/build/install/include -pthread -L ../mongodb/mongo-cxx-driver/build/install/lib -lmongoclient -Dcimg_display=0 -Dcimg_use_png -lpng -lboost_thread -lboost_system -lboost_regex


eigen:
	g++ src/main_eigen.cpp -o eigen ../mongodb/srcs/csvReader.cpp  ../libimg/srcs/img_decompress.cpp   -I ../libcv/inc -I ../mongodb/inc  -I ../CImg-1.6.3/ -I ../libmath/inc/ -I ../libimg/inc/ -std=c++11 -O2 -lm -lpthread -I ~/.brew/Cellar/boost/1.58.0/include/ -I ../mongodb/mongo-cxx-driver/build/install/include -pthread -L ../mongodb/mongo-cxx-driver/build/install/lib -lmongoclient -Dcimg_display=0 -Dcimg_use_png -lpng -lboost_thread -lboost_system -lboost_regex

re: clean nn eigen

clean:
	rm -rf ../eigen ../nn ../front/lastTestSession.txt || true

