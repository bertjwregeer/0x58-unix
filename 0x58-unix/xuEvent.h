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

#ifndef x58UNIX_UEVENT_H
#define x58UNIX_UEVENT_H

namespace x58unix {
        class xuEvent  {
        public:
                xuEvent ();
                virtual ~xuEvent() const = 0;
                
                /*                   callback,    fd, oneshot, clear
                 * callback: Called when the event returns
                 * fd: File descriptor
                 * oneshot: Once the event returns, and the callback has been fired
                 *          remove the event from the system.
                 * clear: After each time the event returns the state of the event
                 *          is reset to neutral. Basically readding the event back
                 *          causing it to be reported as fired again the next time
                 *          the state changes to be true for the event.
                **/
                
                virtual bool ev_read(xuEventcb *, int, bool, bool) const = 0;
                virtual bool ev_write(xuEventcb *, int, bool, bool) const = 0;
                
                /*                    callback,    fd, oneshot, clear, special flags
                 * The rest of the paramaters stay the same, the only thing that changes
                 * is the fact that the vnode can take what sort of actions to look for.
                 * Ex:
                 * ev_vnode(xuEventcb *, 6, false, true, vnode::removed | vnode::write)
                 * where 6 is a valid open file descriptor to a file that is to be monitored
                **/
                const static struct vnode {
                        const static int removed = (1 << 0);
                                // Set this to be notified if the file gets removed
                        const static int write = (1 << 1);
                                // Set this to be notified if the file gets written to (can include negative)
                        const static int extend = (1 << 2);
                                // Set this to be notified if the file gets extended
                        const static int attrib = (1 << 3);
                                // Set this to be notified if the file gets it's attributes changed
                        const static int link = (1 << 4);
                                // Set this to be notified if the link count for the file changes
                        const static int rename = (1 << 5);
                                // Set this to be notified if the file was renamed
                        const static int revoke = (1 << 6);
                                // Set this to be notified if file access has been revoked with revoke(2);
                };
                
                virtual bool ev_vnode(xuEventcb *, int, bool, bool, unsigned int) const = 0;
                virtual bool ev_proc() const = 0;
                virtual bool ev_signal() const = 0;
                virtual bool ev_timer() const = 0;

                class xuEventcb  {
                public:
                        xuEventcb();
                        ~xuEventcb();
                };
        private:
        };
}


#endif /* x58UNIX_UEVENT_H */
