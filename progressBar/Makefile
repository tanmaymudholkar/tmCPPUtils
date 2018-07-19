# Remember: order of arguments to g++ is important, the `root-config` must follow the rest of the arguments

libtmProgressBar.a: src/tmProgressBar.cpp include/tmProgressBar.h
	g++ -c -Wall -Wextra -Werror -pedantic -std=c++11 -fPIC -O3 -o obj/tmProgressBar.o src/tmProgressBar.cpp
	ar crf lib/libtmProgressBar.a obj/tmProgressBar.o

clean:
	rm -rf lib/*
	rm -rf obj/*
	rm -rf bin/*
