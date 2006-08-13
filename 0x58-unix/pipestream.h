/**
 * Copyright 2006 Bert JW Regeer. All rights  reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and  documentation are
 * those of the authors and should not be  interpreted as representing official
 * policies, either expressed  or implied, of bsdPanel project.
 *
**/

#ifndef x58UNIX_PIPESTREAM
#define x58UNIX_PIPESTREAM

#include <istream>
#include <ostream>
#include <streambuf>
#include <iostream>
#include <cstring>

#include <unistd.h>

namespace x58unix {
        
        /**
         * pipeoutbuf is a class which extends streambuf and defines the virtual 
         * function named overflow and xsputn which allow us to send the data
         * over a pipe named "fd" using write.
         *
         * To create an output buffer is simple, according to the standard the only
         * function that has to be overriden is the overflow function. See streambuf
         * in the standard. We also override xsputn since it allows for a more efficient
         * implementation that can write multiple characters to the file descriptor.
        **/
        
        class pipeoutbuf : public std::streambuf {
                public:
                        pipeoutbuf () : _fd(-1) {};
                        pipeoutbuf (int fd) : _fd(fd) {}
                        ~pipeoutbuf () {
                                close(_fd);
                        }
                        
                        void attach (int fd) {
                                if (_fd != -1) close (_fd);
                                _fd = fd;
                        }
                        
                        int ogetfd () {
                                return _fd;
                        }
                        
                protected:
                        int _fd;
                        
                        // Write one character
                        virtual int_type overflow (int_type g) {
                                if (_fd == -1) return traits_type::eof();
                                
                                if (g != traits_type::eof()) {
                                        char z = g;
                                        if (write (_fd, &z, 1) != 1) {
                                                return traits_type::eof();
                                        }
                                }
                        return g;
                        }
                        
                        virtual std::streamsize xsputn (const char* s, std::streamsize num) {
                                if (_fd == -1) return traits_type::eof();
                                return write(_fd, s, num);
                        }
        };
        
        /**
         * opipestream, just a basic wrapper which extends std::ostream. When you call 
         * it, you pass it an "fd" which is an open file descriptor, and from then on
         * you can use it like you would use cout. x58unix::opipestream blah(write[0]);
         * blah << someString;
        **/
        
        class opipestream : public std::ostream {
                public:
                        opipestream (int fd = -1) : std::ostream(0), _buf(fd) {
                                rdbuf(&_buf);
                        }
                        
                        void attach (int fd) {
                                flush();
                                _buf.attach(fd);
                        }
                        
                        int getfd () {
                                return _buf.ogetfd();
                        }
                protected:
                        pipeoutbuf _buf;
        };
        
        /**
         * pipeinbuf is a class which extends std::streambuf. It is used for buffering
         * when reading from pipes. It reads from a standard file descriptor.
         *
         * Pointer arithmetic is a pain in the ass, as are character arrays!
         *
         * To create a input buffer according to the standard only one function
         * has to be overriden, underflow(), see streambuf in the standard for
         * more information. It is in underflow() that all the logic is held
         * for the putback area, as the rest is done through the functions
         * egptr, gptr, eback, which are pointers which are set through setg
         * in the function underflow() and constructor.
        **/
        
        class pipeinbuf : public std::streambuf {
                protected:
                        int _fd;
                        
                        /**
                         * data buffer:
                         * at most, pbSize characters in putback area plus
                         * at most, bufSize characters in ordinary read buffer
                        **/
                         
                         static const int pbSize = 8;           // size of putback area
                         static const int bufSize = 1024;       // size of the data buffer
                         char buffer[bufSize+pbSize];           // The actual buffer
                public:
                        /**
                         * Constructor takes an file descriptor
                         * - Use setg to set the beginning pointer, read pointer, and the end pointer
                         * since they are all the same, the next character extraction will cause an
                         * underflow();
                        **/
                         
                        pipeinbuf () : _fd(-1) {}
                         
                        pipeinbuf (int fd) : _fd(fd) {
                                if (_fd != -1)
                                        setg (buffer+pbSize,            // No putback
                                                buffer+pbSize,          // read pointer
                                                buffer+pbSize);         // end pointer
                        }
                        
                        ~pipeinbuf() {
                                close(_fd);
                        }
                        
                        void attach(int fd) {
                                if (_fd != -1) close(_fd);
                                
                                setg (buffer+pbSize, buffer+pbSize, buffer+pbSize);
                                _fd = fd;
                        }
                        
                        int igetfd() {
                                return _fd;
                        }
                        
                protected:
                        // insert new characters into the buffer
                        virtual int_type underflow () {
                                // is read position before end of buffer
                                if (gptr() < egptr()) {
                                        // No need to read more characters, return the next available one
                                        return traits_type::to_int_type(*gptr());
                                }
                                
                                /* process size of putback area
                                 * - use number of characters read
                                 * - but at most size of putback area
                                 */
                                 
                                int numPutback;
                                numPutback = gptr() - eback();
                                if (numPutback > pbSize) {
                                       numPutback = pbSize;
                                }
        
                                /* copy the last few read
                                 * memmove is used, it does a non-destructive copy. See memmove(3)
                                 */
                                
                                memmove (buffer+(pbSize-numPutback), gptr()-numPutback, numPutback);

                                // read at most bufSize new characters
                                int num;
                                num = read(_fd, buffer+pbSize, bufSize);
                                if (num <= 0) {
                                        // ERROR or EOF
                                        return traits_type::eof();
                                }
                                
                                // reset buffer pointers
                                setg (buffer+(pbSize-numPutback),       // beginning of putback area
                                        buffer+pbSize,                  // read position
                                        buffer+pbSize+num);             // end of buffer
                                
                                // return next character
                                return traits_type::to_int_type(*gptr());
                        }
        };

        /*
         * opipestream, just a basic wrapper which extends std::istream. When you call 
         * it, you pass it an "fd" which is an open file descriptor, and from then on
         * you can use it like you would use cin. bsdPanel::ipipestream blah(read[1]);
         * ipipestream >> someString;
         */
         
        class ipipestream : public std::istream {
                
                public:                        
                        ipipestream (int fd = -1) : std::istream(0), _buf(fd) {
                                rdbuf(&_buf);
                        }
                        
                        void attach (int fd) {
                                _buf.attach(fd);
                        }
                        
                        int getfd() {
                                return _buf.igetfd();
                        }
                
                protected:
                        pipeinbuf _buf;
        };    
}

#endif