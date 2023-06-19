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
	server.sin_addr.s_addr = htonl(INADDR_ANY);	
	
	if(bind(sd, (struct sockaddr *) &server, sizeof(server)) < 0){
		perror("Socket binding failed\n");
		exit(1);
	}
	
	listen(sd, 5);
	
	int data, client_len;
	struct sockaddr_in client;
	
	printf("Awaiting client request\n");
	
	if((data = accept(sd, (struct sockaddr *) &client, &client_len)) < 0){
		perror("Failed to accept");
		exit(1);
	}
	
	read(data, buffer, sizeof(buffer));
	
	printf("Client request received\n");
	
	
	
	char temp;
	
	int len = strlen(buffer);
	
	for(int i = 0; i<len/2; i++){
		temp = buffer[i];
		buffer[i] = buffer[len - i - 1];
		buffer[len - i - 1] = temp;
	}
	
	write(data, buffer, sizeof(buffer));
	printf("Client response send\n");
	
	printf("Connection closed\n");
	close(data);
	close(sd);
		
	return 0;
	
}
