# Remember: order of arguments to g++ is important, the `root-config` must follow the rest of the arguments

helloWorld: main.o
	g++ -o bin/helloWorld obj/main.o -L../argumentParser/lib -ltmArgumentParser `root-config --cflags --glibs`

main.o: src/main.cpp include/main.h
	g++ -c -Wall -Wextra -Werror -pedantic -std=c++11 -fPIC -O3 -o obj/main.o src/main.cpp -I../argumentParser/include `root-config --cflags --glibs`

clean:
	rm -rf bin/*
	rm -rf obj/*
	rm -rf lib/*
