# Remember: order of arguments to g++ is important, the `root-config` must follow the rest of the arguments

helloWorld: main.o
	g++ -o bin/helloWorld obj/main.o -L$(TMCPPUTILS)/argumentParser/lib -ltmArgumentParser -L$(TMCPPUTILS)/progressBar/lib -ltmProgressBar `root-config --cflags --glibs`

main.o: src/main.cpp include/main.h
	g++ -c -Wall -Wextra -Werror -pedantic -std=c++11 -fPIC -O3 -o obj/main.o src/main.cpp -I$(TMCPPUTILS)/argumentParser/include -I$(TMCPPUTILS)/progressBar/include `root-config --cflags --glibs`

clean:
	rm -rf bin/*
	rm -rf obj/*
	rm -rf lib/*
