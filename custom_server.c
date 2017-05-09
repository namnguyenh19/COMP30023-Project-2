/* A simple server in the internet domain using TCP
The port number is passed as an argument


 To compile: gcc server.c -o server
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char **argv)
{
	int sockfd, newsockfd, portno, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
  char exitMess[6] = "shut\n\0";

	if (argc < 2)
	{
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}

	 /* Create TCP socket */

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		perror("ERROR opening socket");
		exit(1);
	}


	bzero((char *) &serv_addr, sizeof(serv_addr));

	portno = atoi(argv[1]);

	/* Create address we're going to listen on (given port number)
	 - converted to network byte order & any IP address for
	 this machine */

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);  // store in machine-neutral format

	 /* Bind address to the socket */

	if (bind(sockfd, (struct sockaddr *) &serv_addr,
			sizeof(serv_addr)) < 0)
	{
		perror("ERROR on binding");
		exit(1);
	}

	clilen = sizeof(cli_addr);

  /* Listen on socket - means we're ready to accept connections -
   incoming connection requests will be queued */

  listen(sockfd,5);

  /* Accept a connection - block until a connection is ready to
   be accepted. Get back a new file descriptor to communicate on. */

  newsockfd = accept(	sockfd, (struct sockaddr *) &cli_addr,
            &clilen);
  if (newsockfd < 0)
  {
    perror("ERROR on accept");
    exit(1);
  }

  while (1) {
  	bzero(buffer,256);

  	/* Read characters from the connection,
  		then process */

  	n = read(newsockfd,buffer,255);

  	if (n < 0)
  	{
  		perror("ERROR reading from socket");
  		exit(1);
  	}

    if (strncmp(buffer, exitMess, 6)==0){
      close(sockfd);
      return 0;
    }

  	printf("Here is the message: %s\n",buffer);

  	n = write(newsockfd,"I got your message\n",19);

  	if (n < 0)
  	{
  		perror("ERROR writing to socket");
  		exit(1);
  	}
  }

	/* close socket */

	close(sockfd);

	return 0;
}
