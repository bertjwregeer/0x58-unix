OPTIMIZE ?=0
CXXFLAGS = -shared -fPIC -I. -I.. -Wall -pipe -O${OPTIMIZE} ${DEBUG}

ALLDEPENDS = Fork.o Pipe.o Exec.o EventAll.o 
ALL = ${ALLDEPENDS} libx58unix.a

all: ${ALL}

libx58unix.a: ${ALLDEPENDS}
	/usr/bin/ar rcs libx58unix.a $>

Fork.o: Fork.cc Fork.h Exceptions.h Chain.h
Pipe.o: Pipe.cc Pipe.h Fork.h Exceptions.h Chain.h
Exec.o: Exec.cc Exec.h Pipe.h Fork.h Exceptions.h Chain.h

Event.o: Event.cc Event.h Exceptions.h

eventKqueue.o: eventKqueue.cc eventKqueue.h Event.h Exceptions.h

EventAll.o: Event.o eventKqueue.o
	ld -r $> -o $@
.cc.o:
	$(CXX) ${CXXFLAGS} -c $<
	
clean:
	/bin/rm -f *.o
	/bin/rm -f *.a
	/bin/rm -f *~
