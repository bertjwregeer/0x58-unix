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

#ifndef x58UNIX_XUSTREAMS
#define x58UNIX_XUSTREAMS

#include <istream>
#include <ostream>
#include <streambuf>
#include <iostream>
#include <cstring>

#include <unistd.h>


namespace x58unix {
	class xufdoutbuf : public std::streambuf {
		public:
			xufdoutbuf (int fd) : _fd(fd) { };
			~xufdoutbuf () {
				close(_fd);
			}

			void attach (int fd) {
				if (_fd != -1) close (_fd);
				_fd = fd;
			}
		
			int retfd () {
				return _fd;
			}

		protected:
			// File descriptor for the file stream
			int _fd;

			// Overload functions overflow and xsputn
		private:
			xufdoutbuf ();
	};

	class xufdinbuf : public std::streambuf {
		protected:
			// File descriptor for the file stream
			int _fd;
		public:	
			xufdinbuf (int fd) : _fd(fd) { };
			~xufdinbuf () {
				close(_fd);
			}

			void attach (int fd) {
				if (_fd != -1) close(_fd);
				_fd = fd;
			}
			
			int retfd() {
				return _fd;
			}

		protected:
			// Overload functions underflow. Putback area required?

		private:
			xufdinbuf();
	};

	class ofdstream : public std::ostream {
		public:
			ofdstream (int fd = -1) : std::ostream(0), _buf(fd) {
				rdbuf(&_buf);
			}

			// implement overloaded = operator. This allows one to do:
			// oFdstream *myStream = new oFdstream();
			// (*myStream) = <fd>;
			// Easier to read what is meant, and makes them act more like file_t's.
			
			ofdstream& operator=(const int fd) {
				_buf.attach(fd);
				return *this;
			}

			// Some people might want access to the fd associated with the stream
			// We give them a std::pair, wether it is read or write, or both. If 
			// it is an out stream, only the first one will be set, the second will
			// be -1. Which is always an invalid fd in the unix world.

			std::pair<int, int> getfd () {
				std::pair<int, int> fds;
				fds.first = _buf.retfd();
				fds.second = -1;
				return fds;
			}
		
		protected:
			xufdoutbuf _buf;
	};

	class ifdstream : public std::istream {
		public:
			ifdstream (int fd = -1) : std::istream(0), _buf(fd) {
				rdbuf(&_buf);

			}

			// See comment in oFdstream. Overload the = operator
			
			ifdstream& operator=(const int fd) {
				_buf.attach(fd);
				return *this;
			}

			// Some people might want access to the fd associated with the stream
			// We give them a std::pair, wether it is read or write, or both. If
			// it is to be an in stream, only the second onewill be set, the first will
			// be -1. Which will always an invalid fd in the unix world.

			std::pair<int, int> getfd () {
				std::pair<int, int> fds;
				fds.first = -1;
				fds.second = _buf.retfd();
				return fds;
			}
		protected:
			xufdinbuf _buf;
	};

} /* x58unix */

#endif
