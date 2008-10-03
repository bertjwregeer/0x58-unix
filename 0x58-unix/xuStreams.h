/**
 * Copyright (c) 2008 Bert JW Regeer <xistence@0x58.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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
