#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define max_msg_len 100

#define DEST_IP "127.0.0.1"
#define DEST_PORT 8080

int main() {
   printf("Client starting...");
   int socketfd = socket(PF_INET, SOCK_STREAM, 0); // create a socket file descriptor

   struct sockaddr_in addr;
   addr.sin_family = PF_INET;
   addr.sin_port = htons(DEST_PORT);

   if (inet_aton(DEST_IP, &addr.sin_addr))
      printf("Bound IP address\n");
   else
      printf("Server Error: Invalid IP");

   if (connect(socketfd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
      printf("Client Error: Failed to connect to server\n");
   else
      printf("Client connected to server\n");

   const char msg[max_msg_len] = "Batman has no parents.";

   int bytes_sent = send(socketfd, msg, strlen(msg), 0);
   if (bytes_sent == -1)
      printf("Client Error: Failed to send msg to server\n");
   else if (bytes_sent < strlen(msg))
      printf("Client Error: Only sent %d to server\n", bytes_sent);
   else
      printf("Successfully sent msg to server\n");

   close(socketfd); // delete the current socket descriptor, disallowing any further connection.

   return 0;
}
