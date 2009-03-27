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

#include <0x58-unix/eventKqueue.h>
namespace x58unix {
        namespace eventImplementation {
                eventKqueue::eventKqueue() {
                        _kq = kqueue();
                }

                eventKqueue::~eventKqueue() {
                        close(_kq);
                }

                bool eventKqueue::_addEvent(uintptr_t ident, short filter, u_short flags, u_int fflags, intptr_t data, void *udata) {
                        // This is the new kevent we are going to add to the queue
                        struct kevent change;
        
                        // We need a timespec that is going to let us return immediatly
                        struct timespec ts;
                        ts.tv_sec = 0;
                        ts.tv_nsec = 0;
        
                        // Add the event, enable the event, and make sure that each time through we clear the state of the event.
                        flags |= (EV_ADD | EV_ENABLE | EV_CLEAR);
        
                        // Use a macro to fill kevent.
                        /**
                                TODO Change this from the macro to actual code? Might be beneficial.
                        **/
        
                        EV_SET(&change, ident, filter, flags, fflags, data, udata);
        
                        // Add the event to the kqueue, we tell it we just want to add 1 and immediatly return using the timespec we have set up
                        if (kevent(_kq, &change, 1, 0, 0, &ts) < 0) {
                                // Failure. Return false
                                perror("kqueue: ");
                                return false;
                        }
        
                        return true;
                }

                bool eventKqueue::read(int fd, bool oneshot, void * cb) 
                {
                        // Create the flags short, this is going to contain the flags we want to enable
                        unsigned short flags = 0;
                        if (oneshot) flags |= EV_ONESHOT;
        
                        return _addEvent(fd, EVFILT_READ, flags, 0, 0, (void *)cb);

                }

                bool eventKqueue::write(int fd, bool oneshot, void * cb) 
                {
                        unsigned short flags = 0;
                        if (oneshot) flags |= EV_ONESHOT;
        
                        return _addEvent(fd, EVFILT_WRITE, flags, 0, 0, (void *)cb);
                }

                void eventKqueue::dispatch() {
                        /**
                                FIXME Actually have the function return the kevents. Choose between function pointers or having a seperate class
                        **/
        
                        struct kevent event;
        
                        while (1) {
                                int nev = kevent(_kq, 0, 0, &event, 1, 0);
                
                                if (nev == -1) {
                                        perror("kqueue: ");
                                        throw x58unix::DispatchFailed();
                                }
                        }
                }
        }
}
