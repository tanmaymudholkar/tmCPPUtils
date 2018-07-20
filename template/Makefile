# Remember: order of arguments to g++ is important, the `root-config` must follow the rest of the arguments

vpath %.a lib
vpath %.so lib
vpath %.o obj
vpath %.cpp src
vpath %.h include
vpath % bin

helloWorld: main.o
	g++ -o bin/helloWorld obj/main.o -L$(TMCPPUTILS)/generalUtils/lib -ltmGeneralUtils `root-config --cflags --glibs`

main.o: main.cpp main.h
	g++ -c -Wall -Wextra -Werror -pedantic -std=c++11 -fPIC -O3 -o obj/main.o src/main.cpp -I$(TMCPPUTILS)/generalUtils/include `root-config --cflags --glibs`

clean:
	rm -rf bin/*
	rm -rf obj/*
