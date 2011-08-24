CXX_OPTS=-std=c++0x -DBOOST_SPIRIT_DEBUG

all: prog

clean:
	rm -f *.o
	rm -f prog

prog: main.o passwd_utils.o
	$(CXX) $(CXX_OPTS) -o $@ $+

main.o: main.cxx passwd_utils.hxx
	$(CXX) $(CXX_OPTS) -c $<

passwd_utils.o: passwd_utils.cxx parser.hxx passwd_utils.hxx
	$(CXX) $(CXX_OPTS) -c $<



