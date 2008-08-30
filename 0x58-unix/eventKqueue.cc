/**
 * Copyright 2008 Bert JW Regeer. All rights  reserved.
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

#include <0x58-unix/eventKqueue.h>

x58unix::eventImplementation::eventKqueue::eventKqueue() {
        _kq = kqueue();
}

x58unix::eventImplementation::eventKqueue::~eventKqueue() {
        close(_kq);
}

bool x58unix::eventImplementation::eventKqueue::_addEvent(uintptr_t ident, short filter, u_short flags, u_int fflags, intptr_t data, void *udata) {
        // This is the new kevent we are going to add to the queue
        struct kevent change;
        
        // We need a timespec that is going to let us return immediatly
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = 0;
        
        // Use a macro to fill kevent
        EV_SET(&change, ident, filter, flags, fflags, data, udata);
        
        // Add the event to the kqueue, we tell it we just want to add 1 and immediatly return using the timespec we have set up
        if (kevent(_kq, &change, 1, 0, 0, &ts) < 0) {
                // Failure. Return false
                perror("kqueue: ");
                return false;
        }
        
        return true;
}

bool x58unix::eventImplementation::eventKqueue::read(void * cb, int fd, bool oneshot, bool clear) 
{
        unsigned int flags = EV_ADD | EV_ENABLE;
        if (oneshot) flags |= EV_ONESHOT;
        if (clear)   flags |= EV_CLEAR;
        
        return _addEvent(fd, EVFILT_READ, flags, 0, 0, (void *)cb);

}

bool x58unix::eventImplementation::eventKqueue::write(void * cb, int fd, bool oneshot, bool clear) 
{
        unsigned int flags = EV_ADD | EV_ENABLE;
        if (oneshot) flags |= EV_ONESHOT;
        if (clear)   flags |= EV_CLEAR;
        
        return _addEvent(fd, EVFILT_WRITE, flags, 0, 0, (void *)cb);
}

void x58unix::eventImplementation::eventKqueue::dispatch() {
        struct kevent event;
        
        while (1) {
                int nev = kevent(_kq, 0, 0, &event, 1, 0);
                
                if (nev == -1) {
                        perror("kqueue: ");
                        throw x58unix::DispatchFailed();
                }
        }
}