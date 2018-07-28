# Remember: order of arguments to g++ is important, the `root-config` must follow the rest of the arguments

vpath %.a lib
vpath %.so lib
vpath %.o obj
vpath %.cpp src
vpath %.h include
vpath % bin

getROOTFileContents: getROOTFileContents.o
	g++ -o bin/getROOTFileContents obj/getROOTFileContents.o -L$(TMCPPUTILS)/generalUtils/lib -ltmGeneralUtils `root-config --cflags --glibs`

getROOTFileContents.o: getROOTFileContents.cpp getROOTFileContents.h
	g++ -c -Wall -Wextra -Werror -pedantic -std=c++11 -fPIC -O3 -o obj/getROOTFileContents.o src/getROOTFileContents.cpp -I$(TMCPPUTILS)/generalUtils/include `root-config --cflags --glibs`

clean:
	rm -rf bin/*
	rm -rf obj/*
