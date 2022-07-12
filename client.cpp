#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 9998
#define HOST "127.0.0.1"
#define SA struct sockaddr

int main(int argc, char **argv)
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(HOST);
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	std::string buff;
	std::string num_str;
	int len = 300000;

	buff += "{";

	for (int i=0; i<len; i++)
	{
		num_str = std::to_string(i);
		buff += "\"msg-type" + num_str + "\": \"stringa\", \"number" + num_str + "\": " + num_str;
		if (i != len-1)
			buff += ",";
	}
	buff += "}<<END>>";
	
	buff = "{ \"first\": \"James\", \"last\": \"Bond\", \"nums\": [0, 0, 7] }";

	printf("%s\n", buff.c_str());
	write(sockfd, buff.c_str(), buff.size());
	close(sockfd);
}
