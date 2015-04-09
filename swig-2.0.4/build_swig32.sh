#!/bin/sh

./configure --prefix=/data/ericliu/Infra_proj/dev/src/thirdparty/swig --with-swiglibdir=../swig/share/swig

#use gcc 4.1.2
make CC=/usr/bin/gcc CXX=/usr/bin/g++ CFLAGS="-m32" CXXFLAGS="-m32" LDFLAGS="-L.."

make install

#thirdparty/swig/bin/swig -swiglib

