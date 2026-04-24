#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
   printf("sub bro\n");
   int socketfd = socket(PF_INET, SOCK_STREAM, 0); // create a socket file descriptor

   sockaddr_in addr;
   addr.sin_family = PF_INET;
   addr.sin_port = htons(8080);

   if (inet_aton("127.0.0.1", &addr.sin_addr))
      printf("Binary address: %u\n", addr.sin_addr.s_addr);
   else
      printf("Error: Invalid IP address format.\n");

   if (bind(socketfd, (sockaddr *)(&addr), sizeof(addr)) == -1)
      printf("Error: Failed to bind address to socket\n");
   else
      printf("Successfully bound address to socket\n");

   constexpr int CONNECTION_LIMIT = 5;
   if (listen(socketfd, CONNECTION_LIMIT) == -1)
      printf("Error: Failed to listen");
   else
      printf("Listening...");

   while (true) {
      int sin_size = sizeof(struct sockaddr_in);
      int connected_socketfd;  // socket fd to communicate with a client
      sockaddr_in client_addr; // ip addr of the client

      connected_socketfd = accept(socketfd, (sockaddr *)&client_addr, (socklen_t *)&sin_size);
      if (connected_socketfd == -1)
         printf("Error: Failed to accept connection");
      else
         printf("Listening...");

      constexpr int max_msg_len = 100;
      char incoming_msg[max_msg_len];

      int msg_signal = recv(connected_socketfd, incoming_msg, max_msg_len, 0);
      if (msg_signal == -1) {
         printf("Error: Failed to receive msg");
      } else if (msg_signal == 0) {
         printf("Client closed connection");
      } else
         printf("Msg received");

      // TODO:: send response to client
      // TODO:: use epoll for non-blocking the program

      close(socketfd); // delete the current socket descriptor, disallowing any further connection.
   }

   return 0;
}
