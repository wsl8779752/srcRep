all:main
main: main.o 
	g++ $^ -o $@


.PHONY: clean
clean:
	-rm main *.o 

souces = main.cpp
include  $(sources:.cpp=.d)

.d:.cpp
	set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
