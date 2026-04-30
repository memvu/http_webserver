#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define max_msg_len 100

#define DEST_IP "127.0.0.1"
#define DEST_PORT 8080

int main() {
   printf("Server starting...");
   int socketfd = socket(PF_INET, SOCK_STREAM, 0); // create a socket file descriptor

   struct sockaddr_in addr;
   addr.sin_family = PF_INET;
   addr.sin_port = htons(DEST_PORT);

   if (inet_aton(DEST_IP, &addr.sin_addr))
      printf("Bound IP address\n");
   else
      printf("Server Error: Invalid IP");

   if (bind(socketfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
      printf("Error: Failed to bind address to socket\n");
   else
      printf("Successfully bound address to socket\n");

   const int CONNECTION_LIMIT = 5;
   if (listen(socketfd, CONNECTION_LIMIT) == -1)
      printf("Error: Failed to listen\n");
   else
      printf("Listening...\n");

   while (1) {
      int sin_size = sizeof(struct sockaddr_in);
      int connected_socketfd;         // socket fd to communicate with a client
      struct sockaddr_in client_addr; // ip addr of the client

      connected_socketfd = accept(socketfd, (struct sockaddr *)&client_addr, (socklen_t *)&sin_size);
      if (connected_socketfd == -1)
         printf("Error: Failed to accept connection\n");
      else
         printf("Listening...\n");

      char incoming_msg[max_msg_len];

      int msg_signal = recv(connected_socketfd, incoming_msg, max_msg_len, 0);
      if (msg_signal == -1) {
         printf("Error: Failed to receive msg\n");
      } else if (msg_signal == 0) {
         printf("Client closed connection\n");
      } else
         printf("Msg received: %s\n", incoming_msg);

      // TODO:: send response to client
      // TODO:: use epoll for non-blocking the program

      close(connected_socketfd); // delete the current socket descriptor, disallowing any further connection.
   }

   return 0;
}
