vpath %.a lib
vpath %.so lib
vpath %.o obj
vpath %.cpp src
vpath %.h include

libtmGeneralUtils.a: tmArgumentParser.o tmProgressBar.o tmMiscellaneous.o
	ar crf lib/libtmGeneralUtils.a obj/tmArgumentParser.o obj/tmProgressBar.o obj/tmMiscellaneous.o

tmArgumentParser.o: tmArgumentParser.cpp tmArgumentParser.h
	g++ -c -Wall -Wextra -Werror -pedantic -std=c++11 -fPIC -O3 -o obj/tmArgumentParser.o src/tmArgumentParser.cpp

tmProgressBar.o: tmProgressBar.cpp tmProgressBar.h
	g++ -c -Wall -Wextra -Werror -pedantic -std=c++11 -fPIC -O3 -o obj/tmProgressBar.o src/tmProgressBar.cpp

tmMiscellaneous.o: tmMiscellaneous.cpp tmMiscellaneous.h
	g++ -c -Wall -Wextra -Werror -pedantic -std=c++11 -fPIC -O3 -o obj/tmMiscellaneous.o src/tmMiscellaneous.cpp

clean:
	rm -rf obj/*.o
	rm -rf lib/*.a
	rm -rf lib/*.so
