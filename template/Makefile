# Remember: order of arguments to g++ is important, the `root-config` must follow the rest of the arguments

helloWorld: main.o
	g++ -o bin/helloWorld obj/main.o `root-config --cflags --glibs`

main.o: src/main.cpp include/main.h
	g++ -Wall -Wextra -Werror -pedantic -std=c++11 -c -o obj/main.o src/main.cpp `root-config --cflags --glibs`
