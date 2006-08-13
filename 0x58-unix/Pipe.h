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
#include <0x58-unix/pipestream.h>

/**
 * The pipe class creates two different pipes. One is for the parent to send data to the child
 * the other is for the child to send data to the parent. After a successfull execution of
 * execute the private _pipes is set to null, so that multiple uses of this class after each
 * other requires the programmer to set up new pipestreams as to not overwrite the old ones,
 * off course it is possible to just pass it the exact same std::pair, and force an overwrite.
**/

namespace x58unix {
	class Pipe : public x58unix::Chain {
		public:
		        typedef std::pair<x58unix::ipipestream, x58unix::opipestream> pair_pipes;
		        
		        Pipe(Chain * chain) : Chain(), _chain(chain), _pipes(0) {}
		        Pipe(Chain * chain, pair_pipes * pipes) 
		                : Chain(), _chain(chain), _pipes(pipes) {}
		        ~Pipe() {}
		        
		        void pipestreams (pair_pipes * pipes) {
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