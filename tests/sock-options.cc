#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

int main () {
        {
                std::cout << "AF_INET SOCK_STREAM 0" << std::endl;
                int sock;
                if( (sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) { 
                        perror("sock-options[socket]"); 
                        exit(-1); 
                }
                int * options = (int *)malloc(sizeof(int));
                socklen_t * len =  (socklen_t *)malloc(sizeof(socklen_t));
                *len = sizeof(int);
        
                if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_SNDBUF       set buffer size for output: "     << *options     << std::endl;
        
                if (getsockopt(sock, SOL_SOCKET, SO_RCVBUF, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_RCVBUF       set buffer size for input: "      << *options     << std::endl;
        
                if (getsockopt(sock, SOL_SOCKET, SO_SNDLOWAT, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_SNDLOWAT     set minimum count for output: "   << *options     << std::endl;
        
                if (getsockopt(sock, SOL_SOCKET, SO_RCVLOWAT, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_RCVLOWAT     set minimum count for input: "    << *options     << std::endl;
        }
        {
                std::cout << "AF_INET SOCK_DGRAM 0" << std::endl;
                int sock;
                if( (sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) { 
                        perror("sock-options[socket]"); 
                        exit(-1); 
                }
                int * options = (int *)malloc(sizeof(int));
                socklen_t * len =  (socklen_t *)malloc(sizeof(socklen_t));
                *len = sizeof(int);
        
                if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_SNDBUF       set buffer size for output: "     << *options     << std::endl;
        
                if (getsockopt(sock, SOL_SOCKET, SO_RCVBUF, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_RCVBUF       set buffer size for input: "      << *options     << std::endl;
        
                if (getsockopt(sock, SOL_SOCKET, SO_SNDLOWAT, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_SNDLOWAT     set minimum count for output: "   << *options     << std::endl;
        
                if (getsockopt(sock, SOL_SOCKET, SO_RCVLOWAT, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_RCVLOWAT     set minimum count for input: "    << *options     << std::endl;
        }
        {
                std::cout << "AF_UNIX SOCK_STREAM 0" << std::endl;
                int sock;
                if( (sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) { 
                        perror("sock-options[socket]"); 
                        exit(-1); 
                }
                int * options = (int *)malloc(sizeof(int));
                socklen_t * len =  (socklen_t *)malloc(sizeof(socklen_t));
                *len = sizeof(int);
        
                if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_SNDBUF       set buffer size for output: "     << *options     << std::endl;
        
                if (getsockopt(sock, SOL_SOCKET, SO_RCVBUF, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_RCVBUF       set buffer size for input: "      << *options     << std::endl;
        
                if (getsockopt(sock, SOL_SOCKET, SO_SNDLOWAT, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_SNDLOWAT     set minimum count for output: "   << *options     << std::endl;
        
                if (getsockopt(sock, SOL_SOCKET, SO_RCVLOWAT, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_RCVLOWAT     set minimum count for input: "    << *options     << std::endl;
        }
        {
                std::cout << "AF_UNIX SOCK_DGRAM 0" << std::endl;
                int sock;
                if( (sock = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) { 
                        perror("sock-options[socket]"); 
                        exit(-1); 
                }
                int * options = (int *)malloc(sizeof(int));
                socklen_t * len =  (socklen_t *)malloc(sizeof(socklen_t));
                *len = sizeof(int);
        
                if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_SNDBUF       set buffer size for output: "     << *options     << std::endl;
        
                if (getsockopt(sock, SOL_SOCKET, SO_RCVBUF, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_RCVBUF       set buffer size for input: "      << *options     << std::endl;
        
                if (getsockopt(sock, SOL_SOCKET, SO_SNDLOWAT, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_SNDLOWAT     set minimum count for output: "   << *options     << std::endl;
        
                if (getsockopt(sock, SOL_SOCKET, SO_RCVLOWAT, options, len) == -1) {
                        perror("sock-options[getsockopt]");
                        exit(-1);
                }
                std::cout << "SO_RCVLOWAT     set minimum count for input: "    << *options     << std::endl;
        }
}