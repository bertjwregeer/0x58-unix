/**
 * Copyright 2007 Bert JW Regeer. All rights  reserved.
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

bool x58unix::eventImplementation::eventKqueue::ev_read(x58unix::xuEvent::xuEventcb * cb, int fd, bool oneshot, bool clear) 
{
        // This is the new kevent we are going to add to the queue
        struct kevent change;
        
        // This is a timespec that we are going to be using to make sure kevent immediatly returns
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = 0;
        
        // Set up the flags
        unsigned int flags = EV_ADD | EV_ENABLE;
        if (oneshot) flags |= EV_ONESHOT;
        if (clear)   flags |= EV_CLEAR;
        
        // Set up the kevent structure with the appropriate information. Callback is stored in the udata section of kqueue
        EV_SET(&change, fd, EVFILT_READ, flags, 0, 0, (void *)cb);
        
        // Add the event to the queue, and since we have a timespec of 0, it returns immediatly, and lets us know if it was successful or not
        if (kevent(_kq, &change, 1, 0, 0, &ts) < 0) {
                // Failure. Return
                perror("kqueue: ");
                return false;
        }
        
        // Everything was fine. Sweet :D.
        return true;
}
