/**
 * Copyright 2006 Bert JW Regeer. All rights  reserved.
 *
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

#include <0x58-unix/Pipe.h>

int x58unix::Pipe::doPipe() {
	if ( pipe(to) == -1) {
		throw x58unix::PipeFailed();
	}

	if ( pipe(from) == -1) {
		throw x58unix::PipeFailed();
	}

	switch ( doFork() ) {
		case 0:
			close(to[1]);        // Close to end of pipe
			close(from[0]);      // Close reading end of pipe
			dup2(to[0], STDIN_FILENO);      // std::cin goes to 0.
                        dup2(from[1], STDOUT_FILENO);    // std::cout goes to 1
			return 0;
		case 1:
			close(to[0]);
			close(from[1]);
                        writer.attach(to[1]);
                        reader.attach(from[0]);
			return 1;
		default:
			throw x58unix::Impossible();
	}
	return 0; // We should never get here!
} 

int x58unix::Pipe::write(const std::string& sendOver) {
        writer << sendOver;
        writer.flush();
        return sendOver.length();
}

int x58unix::Pipe::read(std::string& readOver) {
        std::getline(reader, readOver);
        return readOver.length();
}


x58unix::Pipe::~Pipe() {
        // Close any and all pipes. Don't care if it fails or not
        close(to[0]);
        close(to[1]);
        close(from[0]);
        close(from[1]);
}
