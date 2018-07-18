# Remember: order of arguments to g++ is important, the `root-config` must follow the rest of the arguments

libtmArgumentParser.a: src/tmArgumentParser.cpp include/tmArgumentParser.h
	g++ -c -Wall -Wextra -Werror -pedantic -std=c++11 -fPIC -O3 -o obj/tmArgumentParser.o src/tmArgumentParser.cpp `root-config --cflags --glibs`
	ar crf lib/libtmArgumentParser.a obj/tmArgumentParser.o

clean:
	rm -rf lib/*
	rm -rf obj/*
	rm -rf bin/*
