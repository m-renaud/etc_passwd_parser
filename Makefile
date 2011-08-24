CXX_OPTS=-std=c++0x -DBOOST_SPIRIT_DEBUG

all: prog run

clean:
	rm -f *.o
	rm -f prog
	rm -f etc_pass.xml etc_pass.xml.xml

prog: main.o passwd_utils.o
	$(CXX) $(CXX_OPTS) -o $@ $+

main.o: main.cxx passwd_utils.hxx
	$(CXX) $(CXX_OPTS) -c $<

passwd_utils.o: passwd_utils.cxx parser.hxx passwd_utils.hxx
	$(CXX) $(CXX_OPTS) -c $<

run: etc_pass.xml



etc_pass.xml: indent2.xsl prog
	./prog >$@.xml 2>/dev/null
	xmlstarlet tr indent2.xsl $@.xml >$@
	rm -f $@.xml
