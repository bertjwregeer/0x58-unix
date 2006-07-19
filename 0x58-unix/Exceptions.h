/**
 * Copyright 2006 Bert JW Regeer. All rights  reserved.
 *
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

#ifndef x58UNIX_EXCEPTIONS
#define x58UNIX_EXCEPTIONS

#include <stdexcept>

namespace x58unix {
        class TooManyArgs : public std::runtime_error {
                public:
                        TooManyArgs() 
                                : std::runtime_error("Too many arguments") { };
        };

        class TooManyEnv : public std::runtime_error {
                public:
                        TooManyEnv() 
                                : std::runtime_error("Too many enviroment variables") { };
        };

        class NoArgs : public std::runtime_error {
                public:
                        NoArgs()
                                : std::runtime_error("No arguments provided") { };
        };
        
        class PipeFailed : public std::runtime_error {
                public:
                        PipeFailed() 
                                : std::runtime_error("Pipe creation failed.") { };
        };
        
        class ForkFailed : public std::runtime_error {
                public:
                        ForkFailed() 
                                : std::runtime_error("Fork failed.") { };
        };
        
        class Impossible : public std::runtime_error {
                public:
                        Impossible()
                                : std::runtime_error("This is an impossible code path!") { }
        };
}
#endif
