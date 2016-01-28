#
# Makefile
# gbersac, 2015-07-15 14:43
#

.PHONY: main 

all: main
	@echo "Please run 'export CV_DIR=\`pwd\`' prior to mongoserver.sh and facerecognition executable"

install:
		brew install boost;
		brew install scons;
		brew install mongodb;
		brew install libpng;
		scons install -C mongodb/mongo-cxx-driver --c++11=on --cpppath=$(HOME)/.brew/Cellar/boost/1.58.0/include --libpath=$(HOME)/.brew/Cellar/boost/1.58.0/lib;

linux-install:
		sudo apt-get install libboost-dev;

uninstall:
		brew uninstall boost;
		brew uninstall scons;
		brew uninstall mongodb;
		brew uninstall libpng;

main:
	make -C main $(RULE)

clean:
	make RULE=clean

fclean:
	make RULE=fclean

re:
	make RULE=re
