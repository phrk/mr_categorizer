import sys
import os
import glob
import subprocess

platform = sys.platform
print "PLATFORM:"+platform

_CXX = 'clang++'

_CCFLAGS = '-c -Wall -Wno-return-type -D_REENTRANT -DHAVE_NETINET_IN_H -I/opt/hypertable/current/include \
       -I/opt/hypertable/current/include/thrift \
		-I/opt/hypertable/current/include/ThriftBroker/gen-cpp \
		-I/usr/local/include'

_LINKFLAGS = '-v -rdynamic -L/opt/hypertable/current/lib -lHyperThrift \
        -lHyperCommon -lHypertable -lthrift -levent -llog4cpp -lHyperSpace \
		-lboost_system-mt -lboost_regex-mt -lpthread -lbson -lcurl -lpcrecpp \
		-ljson_linux-gcc-4.2.1_libmt -lprotobuf -lcld2'


cpp_files = [
'../hcrawler/wwwht/TextParsed.cpp',
'../hcrawler/wwwht/TextParsed.pb.cc'
]

cpp_files = cpp_files + Glob('../hspliter/*.cpp')

cpp_files = cpp_files + Glob('../tetramorph/common/*.cpp')

cpp_files = cpp_files + Glob('../tetramorph/mapreduce/core/*.cpp')
cpp_files = cpp_files + Glob('../tetramorph/threadpool/*.cpp')

#cpp_files = cpp_files + Glob('../hcrawler/*.cpp')
#cpp_files = cpp_files + Glob('../hcrawler/wwwht/*.cpp')
cpp_files = cpp_files + Glob('../lang/*.cpp')
cpp_files = cpp_files + Glob('../thirdparty/libstemmer_c/libstemmer/*utf8.c')
cpp_files = cpp_files + Glob('../thirdparty/libstemmer_c/src_c/*UTF*.c')
cpp_files = cpp_files + Glob('../thirdparty/libstemmer_c/runtime/*.c')

cpp_files = cpp_files + Glob('../htdba/*.cpp')

cpp_files = cpp_files + Glob('*.cpp')
cpp_files = cpp_files + Glob('*.cc')

env = Environment()
Program('mr_categorizer', 
[cpp_files
], LIBS=[], LIBPATH='.', CCFLAGS=_CCFLAGS, CXX=_CXX, LINKFLAGS=_LINKFLAGS)
