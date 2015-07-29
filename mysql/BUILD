#[user00@agileops webscalesql-build]$cmake ../webscalesql-5.6-webscalesql-5.6.24 -DCMAKE_C_COMPILER=/usr/local/gcc/4.9.2/bin/gcc -DCMAKE_CXX_COMPILER=/usr/local/gcc/4.9.2/bin/g++ -DBUILD_TYPE=mysql_release -DCMAKE_INSTALL_PREFIX=/data/home/user00/workspace/webscalesql-install -DWITHOUT_SERVER=1
#-- Running cmake version 3.1.0-rc1
#-- MySQL 5.6.24
#-- Packaging as: mysql-5.6.24-Linux-x86_64
#-- HAVE_VISIBILITY_HIDDEN
#-- HAVE_VISIBILITY_HIDDEN
#-- HAVE_VISIBILITY_HIDDEN
#-- Using cmake version 3.1.0-rc1
#-- Not building NDB
#-- Library webscalesqlclient depends on OSLIBS -lpthread;m;rt;dl
#-- CMAKE_BUILD_TYPE: RelWithDebInfo
#-- COMPILE_DEFINITIONS: HAVE_CONFIG_H
#-- CMAKE_C_FLAGS:  -Wall -Wextra -Wformat-security -Wwrite-strings -std=c99
#-- CMAKE_CXX_FLAGS:  -Wall -Wextra -Wformat-security -Woverloaded-virtual -Wno-unused-parameter -std=c++11
#-- CMAKE_C_FLAGS_RELWITHDEBINFO: -O3 -g -fabi-version=2 -fno-omit-frame-pointer -fno-strict-aliasing -DDBUG_OFF
#-- CMAKE_CXX_FLAGS_RELWITHDEBINFO: -O3 -g -fabi-version=2 -fno-omit-frame-pointer -fno-strict-aliasing -DDBUG_OFF
#-- Configuring done
#-- Generating done
#-- Build files have been written to: /data/home/user00/workspace/webscalesql-build

#cp -Prv * /data/home/user00/workspace/thirdparty/mysql/lib64_release

cc_library(name = "webscalesqlclient", prebuilt = 1, deps = [ '#pthread', '#m', '#rt', '#dl' ])
cc_library(name = "webscalesqlclient_r", prebuilt = 1, deps = [ '#pthread', '#m', '#rt', '#dl' ])
