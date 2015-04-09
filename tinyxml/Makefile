tixml_common_sources := tinyxml.cpp tinyxmlparser.cpp tinyxmlerror.cpp

project.targets += libtinyxml.a
libtinyxml.a.type = library
libtinyxml.a.sources = $(tixml_common_sources)
libtinyxml.a.target_bits = 32
libtinyxml.a.path = lib

project.targets += libtinyxmld.a
libtinyxmld.a.type = library
libtinyxmld.a.sources = $(tixml_common_sources)
libtinyxmld.a.target_bits = 32
libtinyxmld.a.path = lib
libtinyxmld.a.debug = 1

project.targets += libtinyxml_nostl.a
libtinyxml_nostl.a.type = library
libtinyxml_nostl.a.sources = $(tixml_common_sources) tinystr.cpp
libtinyxml_nostl.a.defines = TIXML_NO_STL
libtinyxml_nostl.a.target_bits = 32
libtinyxml_nostl.a.path = lib

project.targets += libtinyxmld_nostl.a
libtinyxmld_nostl.a.type = library
libtinyxmld_nostl.a.sources = $(tixml_common_sources)
libtinyxmld_nostl.a.target_bits = 32
libtinyxmld_nostl.a.path = lib
libtinyxmld_nostl.a.debug = 1

ifeq ($(HOSTTYPE), x86_64)
project.targets += libtinyxml64.a
libtinyxml64.a.type = library
libtinyxml64.a.sources = $(tixml_common_sources)
libtinyxml64.a.target_bits = 64
libtinyxml64.a.path = lib64

project.targets += libtinyxml64d.a
libtinyxml64d.a.type = library
libtinyxml64d.a.sources = $(tixml_common_sources)
libtinyxml64d.a.target_bits = 64
libtinyxml64d.a.path = lib64
libtinyxml64d.a.debug = 1

project.targets += libtinyxml64_nostl.a
libtinyxml64_nostl.a.type = library
libtinyxml64_nostl.a.sources = $(tixml_common_sources) tinystr.cpp
libtinyxml64_nostl.a.defines = TIXML_NO_STL
libtinyxml64_nostl.a.target_bits = 64
libtinyxml64_nostl.a.path = lib64

project.targets += libtinyxml64d_nostl.a
libtinyxml64d_nostl.a.type = library
libtinyxml64d_nostl.a.sources = $(tixml_common_sources)
libtinyxml64d_nostl.a.target_bits = 64
libtinyxml64d_nostl.a.path = lib64
libtinyxml64d_nostl.a.debug = 1
endif

project.targets += xmltest
xmltest.sources = xmltest.cpp $(tixml_common_sources)

include ../../common/builder/Generic.mak

