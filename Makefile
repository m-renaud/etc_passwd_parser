CXX_OPTS=-std=c++0x -DBOOST_SPIRIT_DEBUG

all: prog

clean:
	rm -f *.o
	rm -f prog
	rm -f etc_pass.xml etc_pass.xml.xml

prog: main.o etc_passwd_utils_parser.o etc_passwd_utils_generator.o
	$(CXX) $(CXX_OPTS) -o $@ $+

main.o: main.cxx etc_passwd_utils.hxx
	$(CXX) $(CXX_OPTS) -c $<

etc_passwd_utils_parser.o: etc_passwd_utils_parser.cxx parser.hxx etc_passwd_utils.hxx
	$(CXX) $(CXX_OPTS) -c $<

etc_passwd_utils_generator.o: etc_passwd_utils_generator.cxx generator.hxx etc_passwd_utils.hxx
	colorgcc $(CXX_OPTS) -c $<

test: etc_pass.xml

etc_pass.xml: indent2.xsl prog
	./prog test.txt > $@.xml 2>/dev/null
	xmlstarlet tr indent2.xsl $@.xml >$@
	rm -f $@.xml
