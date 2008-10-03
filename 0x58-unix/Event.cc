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
        namespace eventImplementation {
                /**
                        Implement the functionality for EventRoll
                **/
                EventRoll& EventRoll::retrieve() {
                        static EventRoll roll;
                        return roll;
                }
                
                /**
                        TODO Error checking? Or should we assume programmer won't want to shoot himself in his own foot?
                **/
                void EventRoll::enroll (std::string name, event_fptr fptr) {
                        _roll.insert(std::pair<std::string, event_fptr>(name,fptr));
                }
                
                /**
                        FIXME Actually implement search functionality
                **/
                event_fptr EventRoll::search(std::string name) {
                        return 0;
                }
                
                /**
                        Implement the functionality for EventEnroll
                **/
                EventEnroll::EventEnroll(std::string name, event_fptr fptr) {
                        EventRoll::retrieve().enroll(name, fptr);
                }
        }
}
