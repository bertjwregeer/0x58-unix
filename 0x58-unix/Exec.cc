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
 
#include <0x58-unix/Exec.h>
 
x58unix::Exec::Exec(Chain * chain, std::vector<std::string> const & _args) : _chain(chain), args(_args) {
        if (args.size() > MAXARG)
                throw x58unix::TooManyArgs();
        if (args.size() == 0)
                throw x58unix::NoArgs();
}

x58unix::Exec::Exec(Chain * chain, std::vector<std::string> const & _args,  std::vector<std::string> const & _env) : _chain(chain), args(_args), env(_env) {
        if (args.size() > MAXARG)
                throw x58unix::TooManyArgs();
        if (env.size() > MAXARG)
                throw x58unix::TooManyEnv();
        if (args.size() == 0)
                throw x58unix::NoArgs();
}

int x58unix::Exec::execute() {
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

        _chain->execute();
        
        if (_chain->state == _chain->Child) {
                if ( argv && envi == 0 )
                        execv(argv[0], argv);
                if ( argv && envi )
                        execve(argv[0], argv, envi);

                _exit(-1);
        }
        
        if (_chain->state == _chain->Parent) {
                return 1;
        }
        throw x58unix::Impossible();
}                   
