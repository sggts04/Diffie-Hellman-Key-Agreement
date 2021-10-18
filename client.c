#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "miracl.h"
#include <time.h>
#include <arpa/inet.h>
#define MAX 10000
#define PORT 8081
#define SA struct sockaddr

char *primetext=
"155315526351482395991155996351231807220169644828378937433223838972232518351958838087073321845624756550146945246003790108045940383194773439496051917019892370102341378990113959561895891019716873290512815434724157588460613638202017020672756091067223336194394910765309830876066246480156617492164140095427773547319";
time_t seed;
big a,b,p,pa,pb,key;
miracl *mip;

void func(int sockfd) {
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		n = 0;
		char temp;
		temp = getchar();


		bigbits(160,a);
		powltr(3,a,p,pa);
		cotstr(pa,buff);
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		printf("\nPb recieved from Bob = %s\n", buff);

		cinstr(pb,buff);
		powmod(pb,a,p,key);
		printf("\nAlice's Calculated Key (Pb^a mod p) = ");
    	cotnum(key,stdout);
		
		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("Alice Exit...\n");
			break;
		}
	}
}

int main() {
	int sockfd, connfd;
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
	cinstr(p, primetext);

	printf("Using p = %s\n\n", primetext);

	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("Connected to Bob.\n");

	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}
