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

#ifndef x58UNIX_UEVENT_H
#define x58UNIX_UEVENT_H

#include <iostream>
#include <string>
#include <vector>

namespace x58unix {
        
        /**
                TODO Implement other types of events. Went with read and write for now, for simplicity.
        **/
        
        class Event  {
        public:
                // Always require a constructor and a destructor
                Event ();
                virtual ~Event() = 0;
                
                /**
                        Function definitions for the events, contains the following arguments
                        
                        fd      File descriptor for the event, if event does not take a file descriptor it can also be an ident
                        oneshot As soon as the event fires, it is removed from the event mechanism, and the callee will have to re-add it to the queue
                        cb      Call back function pointer.
                **/
                
                virtual bool read(int fd, bool oneshot, void * cb) = 0;
                virtual bool write(int fd, bool oneshot, void * cb) = 0;
                
                /**
                        Once called, waits forever until an event occurs, calls the callback for said event and goes back into a loop. 
                **/
                
                virtual void dispatch() = 0;
                
        private:
        };
        
        namespace eventImplementation {
                template<class E> x58unix::Event* event_factory() {
                        return new E;
                }
                
                typedef x58unix::Event* (*event_fptr)(void);
                
                class EventRegistry  {
                private:
                        typedef struct Event_t
                        {
                                std::string name;
                                int weight;
                                event_fptr fptr;
                        } event_t;
                        
                        std::vector<event_t> _roll;
                        
                public:
                        static EventRegistry& retrieve();
                        event_fptr search(std::string);
                        void enroll(std::string, int, event_fptr);
                        
                        friend std::ostream& operator<< (std::ostream&, const EventRegistry&);
                };
                
                class EventRegister {
                public:
                        EventRegister(std::string, int, event_fptr);
                };
        }
}


#define REGISTER_EVENT(ename, weight, event) x58unix::eventImplementation::EventRegister _event_register_##ename(#ename, weight, &x58unix::eventImplementation::event_factory<event>);
#endif /* x58UNIX_UEVENT_H */
