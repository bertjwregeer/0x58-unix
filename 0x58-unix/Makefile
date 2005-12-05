OPTIMIZE ?=0
CXXFLAGS = -I. -I.. -Wall -pipe -O${OPTIMIZE} ${DEBUG}

ALLDEPENDS = Fork.o Pipe.o Exec.o
ALL = ${ALLDEPENDS} libx58unix.a

all: ${ALL}

Fork.o: Fork.cc Fork.h Exceptions.h
	${CXX} ${CXXFLAGS} -c Fork.cc

Pipe.o: Pipe.cc Pipe.h Fork.h Exceptions.h
	${CXX} ${CXXFLAGS} -c Pipe.cc

Exec.o: Exec.cc Exec.h Pipe.h Fork.h Exceptions.h
	${CXX} ${CXXFLAGS} -c Exec.cc

libx58unix.a: ${ALLDEPENDS}
	/usr/bin/ar rc libx58unix.a *.o
	/usr/bin/ranlib libx58unix.a

clean:
	/bin/rm -f *.o
	/bin/rm -f *.a
