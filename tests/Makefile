CXXFLAGS = -I. -I.. -Wall -pipe -g
LDFLAGS = -L../0x58-unix -lx58unix

ALL = sock-options kqueue-readwrite event-register

all: ${ALL}

event-register: event-register.o
kqueue-readwrite: kqueue-readwrite.o
sock-options: sock-options.o

.cc.o:
	$(CXX) ${CXXFLAGS} -c $<
	
.o:
	$(CXX) ${LDFLAGS} -o $@ $>

clean:
	/bin/rm -f *.o
	/bin/rm -f *.a
	/bin/rm -f *~
	/bin/rm -f ${ALL}
