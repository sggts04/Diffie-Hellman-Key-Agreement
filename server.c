#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "miracl.h"   /* include MIRACL system */
#include <math.h>
#include <time.h>
#define MAX 1000
#define PORT 8081
#define SA struct sockaddr

int state = 0;
char *primetext=
"155315526351482395991155996351231807220169644828378937433223838972232518351958838087073321845624756550146945246003790108045940383194773439496051917019892370102341378990113959561895891019716873290512815434724157588460613638202017020672756091067223336194394910765309830876066246480156617492164140095427773547319";
time_t seed;
big a,b,p,pa,pb,key;
miracl *mip;

// Function designed for chat between client and server.
void func(int sockfd) {
	char buff[MAX];
	int n;
	// infinite loop for chat
	for (;;) {
		bzero(buff, MAX);

		read(sockfd, buff, sizeof(buff));


			printf("Pa recieved from Alice: %s\n", buff);
			cinstr(pa,buff);
			bzero(buff, MAX);

			bigbits(160,b);
    		powltr(3,b,p,pb);
			cotstr(pb,buff);
			write(sockfd, buff, sizeof(buff));

			powmod(pa,b,p,key);
    		cotnum(key,stdout);
			printf("\n\BOB CALCULATED KEY: ");
    		cotnum(key,stdout);
			
			int test;
			scanf("%d", &test);


		// if msg contains "Exit" then server exit and chat ended.
		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}

// Driver function
int main() {
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	#ifndef MR_NOFULLWIDTH   
    mip=mirsys(36,0);
	#else
		mip=mirsys(36,MAXBASE);
	#endif
		a=mirvar(0);
		b=mirvar(0);
		p=mirvar(0);
		pa=mirvar(0);
		pb=mirvar(0);
		key=mirvar(0);

	time(&seed);
    irand((unsigned long)seed);

    printf("First Diffie-Hellman Key exchange .... \n");

    cinstr(p,primetext);

	printf("Using p: %s", primetext);

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("Socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Bob listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("Server accept failed...\n");
		exit(0);
	}
	else
		printf("Alice joined...\n");

	// Function for chatting between client and server
	func(connfd);

	// After chatting close the socket
	close(sockfd);
}
