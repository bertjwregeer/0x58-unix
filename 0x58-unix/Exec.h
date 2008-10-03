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

#ifndef x58UNIX_EXEC
#define x58UNIX_EXEC

#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <memory>
#include <unistd.h>
#include <0x58-unix/Chain.h>
#include <0x58-unix/Exceptions.h>

#define MAXARG 512

namespace x58unix {
        class Exec : public x58unix::Chain {
                public:
                        Exec(Chain * chain, std::vector<std::string> const & _args);
                        Exec(Chain * chain, std::vector<std::string> const & _args, std::vector<std::string> const & _env);
                        ~Exec() {}
                        int execute();
                          
                private:
                        Chain * _chain;
                        std::vector<std::string> args;
                        std::vector<std::string> env;
                        // Private exec without paramaters because reusing this object is a no-no.
                        Exec () {}
                        Exec (Exec&);
                        Exec& operator = (Exec&);
        };
}

#endif
