#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
   printf("sub bro\n");
   int server_socket = socket(PF_INET, SOCK_STREAM, 0);

   sockaddr_in addr;
   addr.sin_family = PF_INET;
   addr.sin_port = htons(8080);

   if (inet_aton("127.0.0.1", &addr.sin_addr))
      printf("Binary address: %u\n", addr.sin_addr.s_addr);
   else
      printf("Error: Invalid IP address format.\n");

   if (bind(server_socket, (sockaddr *)(&addr), sizeof(addr)) != 0)
      printf("Error: Failed to bind address to socket\n");
   else
      printf("Successfully bound address to socket\n");

   return 0;
}
