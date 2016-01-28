#!/bin/sh
brew install scons
brew install boost
scons install --cpppath=$HOME/.brew/Cellar/boost/1.58.0/include --libpath=$HOME/.brew/Cellar/boost/1.58.0/lib --c++11=on
