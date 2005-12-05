/*
 * Copyright 2005 Bert JW Regeer. All rights  reserved.
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
 */
 
#include <0x58-unix/Exec.h>
 
x58unix::Exec::Exec( std::vector<std::string> const & _args) : Pipe(), args(_args) {
        if (args.size() > MAXARG)
                throw x58unix::TooManyArgs();
        if (args.size() == 0)
                throw x58unix::NoArgs();
}

x58unix::Exec::Exec( std::vector<std::string> const & _args,  std::vector<std::string> const & _env) : Pipe(), args(_args), env(_env) {
        if (args.size() > MAXARG)
                throw x58unix::TooManyArgs();
        if (env.size() > MAXARG)
                throw x58unix::TooManyEnv();
        if (args.size() == 0)
                throw x58unix::NoArgs();
}

int x58unix::Exec::doExec() {
        char **argv = 0;
        char **envi = 0;
        
        argv = new char*[args.size() + 1];
        int i = 0;
        for (std::vector<std::string>::iterator a = args.begin(), b = args.end(); 
                a!=b; a++) {
                argv[i] = new char[(a)->length() + 1]; 
                strcpy(argv[i], (a)->c_str());
                i++;
        }
        argv[i] = static_cast<char *> (0);      

        if (env.size() > 0) {
                envi = new char*[env.size() + 1];
                int i = 0;
                for (std::vector<std::string>::iterator a = env.begin(), b = env.end(); 
                        a!=b; a++) {
                        envi[i] = new char[(a)->length() + 1]; 
                        strcpy(envi[i], (a)->c_str());
                        i++;
                }
                envi[i] = static_cast<char *> (0);
        }
        
        switch(doPipe()) {
                case 0:
                        if ( argv && envi == 0 )
                                execv(argv[0], argv);
                        if ( argv && envi )
                                execve(argv[0], argv, envi);
                                                                             
                        _exit(-1);
                        break;
                case 1:
                        return 1;
                default:
                        throw x58unix::Impossible();
                        // If we get here there is a more serious problem :P
        }
        throw x58unix::Impossible();
}                   
