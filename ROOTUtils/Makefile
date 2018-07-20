# Remember: order of arguments to g++ is important, the `root-config` must follow the rest of the arguments

vpath %.a lib
vpath %.so lib
vpath %.o obj
vpath %.cpp src
vpath %.h include

libtmROOTUtils.a: tmROOTSaverUtils.o
	ar crf lib/libtmROOTUtils.a obj/tmROOTSaverUtils.o

tmROOTSaverUtils.o: tmROOTSaverUtils.cpp tmROOTSaverUtils.h
	g++ -c -Wall -Wextra -Werror -pedantic -std=c++11 -fPIC -O3 -o obj/tmROOTSaverUtils.o src/tmROOTSaverUtils.cpp `root-config --cflags --glibs`

clean:
	rm -rf obj/*.o
	rm -rf lib/*.a
	rm -rf lib/*.so
