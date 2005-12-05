OPTIMIZE ?=0
CXXFLAGS = -I. -I.. -Wall -pipe -O${OPTIMIZE} ${DEBUG}

ALLDEPENDS = Exceptions.h
ALL = Fork.o Pipe.o Exec.o libx58unix.a

all: ${ALL}

Fork.o: Fork.cc Fork.h ${ALLDEPENDS}
	${CXX} ${CXXFLAGS} -c Fork.cc

Pipe.o: Pipe.cc Pipe.h Fork.h ${ALLDEPENDS}
	${CXX} ${CXXFLAGS} -c Pipe.cc

Exec.o: Exec.cc Exec.h Pipe.h Fork.h
	${CXX} ${CXXFLAGS} -c Exec.cc

libx58unix.a: Fork.o Pipe.o Exec.o
	/usr/bin/ar rc libx58unix.a *.o
	/usr/bin/ranlib libx58unix.a

clean:
	/bin/rm *.o
	/bin/rm *.a
