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

#ifndef x58UNIX_FORK
#define x58UNIX_FORK

#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <0x58-unix/Chain.h>
#include <0x58-unix/Exceptions.h>

namespace x58unix {
        class Fork : public x58unix::Chain {
        public:
                Fork () {}
                ~Fork () {}
                int execute();
                pid_t pid;

        private:
                Fork (Fork&);
                Fork& operator = (Fork&);
        };
}

#endif
