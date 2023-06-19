#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	struct sockaddr_in server;
	int sd;
	
	char buffer[200];
	
	
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Socket creation failed\n");
		exit(1);
	}
	
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(4200);
	
	inet_pton(AF_INET,"127.0.0.1", &(server.sin_addr));
	
	if(connect(sd, (struct sockaddr *) &server, sizeof(server)) < 0){
		perror("Socket connection failed\n");
		exit(1);
	}
	printf("Enter a string\n");
	fgets(buffer, sizeof(buffer), stdin);
	write(sd, buffer, sizeof(buffer));
	read(sd, buffer, sizeof(buffer));
	printf("Server response received\n");
	printf("%s\n",buffer);
	
	close(sd);
	
	return 0;
	
}
