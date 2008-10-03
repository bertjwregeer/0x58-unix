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
 
#ifndef x58UNIX_PIPE
#define x58UNIX_PIPE

#include <sstream>
#include <fstream>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <0x58-unix/Chain.h>
#include <0x58-unix/Exceptions.h>
#include <0x58-unix/xuStreams.h>

/**
   The pipe class creates two different pipes. One is for the parent to send data to the child
   the other is for the child to send data to the parent. After a successfull execution of
   execute the private _pipes is set to null, so that multiple uses of this class after each
   other requires the programmer to set up new pipestreams as to not overwrite the old ones,
   off course it is possible to just pass it the exact same std::pair, and force an overwrite.
**/

namespace x58unix {
	class Pipe : public x58unix::Chain {
		public:
		        typedef std::pair<x58unix::ifdstream, x58unix::ofdstream> pair_pipes;
		        
		        Pipe(Chain * chain) : Chain(), _chain(chain), _pipes(0) {}
		        Pipe(Chain * chain, pair_pipes * pipes) 
		                : Chain(), _chain(chain), _pipes(pipes) {}
		        ~Pipe() {}
		        
		        void setpipes (pair_pipes * pipes) {
		                _pipes = pipes;
		        }
		        
			int execute();
                private:
                        Chain * _chain;
                        pair_pipes * _pipes;
                        
                        Pipe();
                        Pipe (Pipe&);
                        Pipe& operator = (Pipe&);
	};
}
	
#endif
