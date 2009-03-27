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

#include <0x58-unix/Event.h>

namespace x58unix {
        
        Event::Event() { }
        
        Event::~Event() { }
        
        
        namespace eventImplementation {
                
                EventRegistry& EventRegistry::retrieve() {
                        static EventRegistry roll;
                        return roll;
                }
                
                /**
                        TODO Error checking? Or should we assume programmer won't want to shoot himself in his own foot?
                **/
                void EventRegistry::enroll (std::string name, int weight, event_fptr fptr) {
                        event_t new_event;
                        
                        new_event.name = name;
                        new_event.weight = weight;
                        new_event.fptr = fptr;
                        
                        _roll.push_back(new_event);
                }
                
                /**
                        TODO: Throw an error if the one that is requested is not available!
                **/
                event_fptr EventRegistry::search(std::string name) {
                        
                        for (std::vector<event_t>::iterator a = _roll.begin(), b = _roll.end(); a!=b; a++) {
                                if ((*a).name == name)
                                        return (*a).fptr;
                        }
                        
                        return 0;
                }
                
                EventRegister::EventRegister(std::string name, int weight, event_fptr fptr) {
                        EventRegistry::retrieve().enroll(name, weight, fptr);
                }
        }
        
}
