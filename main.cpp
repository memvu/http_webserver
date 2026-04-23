#include <stdio.h>
#include <sys/socket.h>

int main() {
   printf("sub bro\n");
   int server_socket = socket(PF_INET, SOCK_STREAM, 0);

   return 0;
}
