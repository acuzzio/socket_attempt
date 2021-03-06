#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
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

	std::string buff, filename;
	std::string num_str;

	// filename = "README.md";
	filename = "python_server.py";


	write(sockfd, std::to_string(filename.size()).c_str(), 128);
	write(sockfd, filename.c_str(), filename.size());

	// std::ifstream t("ca0");
	std::ifstream t(filename);
	std::stringstream buffer;
	buffer << t.rdbuf();

	buff += buffer.str();

	write(sockfd, std::to_string(buff.size()).c_str(), 128);
	write(sockfd, buff.c_str(), buff.size());
	close(sockfd);
}
