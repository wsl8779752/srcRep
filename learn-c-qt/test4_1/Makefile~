all: main

main: main.o add1.o sub1.o
	gcc $^ -o $@

clean:
	-rm main *.o

.PHONY: clean

sources = main.cpp add1.cpp sub1.cpp

include $(sources:.cpp=.d)

%.d: %.cpp
	set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
