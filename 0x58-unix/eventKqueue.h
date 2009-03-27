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

#ifndef x58UNIX_EVENTKQUEUE_H
#define x58UNIX_EVENTKQUEUE_H

#include <0x58-unix/Event.h>
#include <0x58-unix/Exceptions.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>


namespace x58unix {
        namespace eventImplementation {
                class eventKqueue : public x58unix::Event {
                public:
                        eventKqueue ();
                        ~eventKqueue ();
                
                        bool read(int, bool, void *);
                        bool write(int, bool, void *);
                        void dispatch();
                        
                private:
                        int _kq;
                        
                        bool _addEvent(uintptr_t ident, short filter, u_short flags, u_int fflags, intptr_t data, void *udata);
                };
        }
}

REGISTER_EVENT(kqueue, 20, x58unix::eventImplementation::eventKqueue);
#endif /* x58UNIX_EVENTKQUEUE_H */
