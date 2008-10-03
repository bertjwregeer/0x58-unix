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

#include <0x58-unix/Pipe.h>

int x58unix::Pipe::execute() {
        // Declare the int array's to be used for pipe!
        int to[2];
        int from[2];
        
        if (_pipes == 0) {
                throw x58unix::NoPipes();
        }
        
	if ( pipe(to) == -1) {
		throw x58unix::PipeFailed();
	}

	if ( pipe(from) == -1) {
	        // Make sure to close the already open to pipes
	        close(to[0]);
	        close(to[1]);
		throw x58unix::PipeFailed();
	}
	
	_chain->execute();

        if (_chain->state == _chain->Child) {
                close(to[1]);        // Close to end of pipe
                close(from[0]);      // Close reading end of pipe
                dup2(to[0], STDIN_FILENO);      // std::cin goes to 0.
                dup2(from[1], STDOUT_FILENO);    // std::cout goes to 1
                
                state = _chain->state;
                return 0;
        }
        if (_chain->state == _chain->Parent) {
                close(to[0]);
                close(from[1]);
                _pipes->second = to[1];           // The input to the forked application
                _pipes->first = from[0];        // The reading from the forked application
                
                state = _chain->state;
                _pipes = 0;                             // This class can be reused
                return 1;
        }
	return 0; // We should never get here!
}
