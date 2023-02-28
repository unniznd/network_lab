#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdlib.h>


struct sockaddr_in servaddr, cliaddr;

int main(){

    int sd;

    sd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sd< 0){
        perror("Socket creation failed\n");
        exit(1);
    }

    bzero((char *)&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int res;
    res = bind(sd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    if(res < 0){
        perror("Binding failed");
        exit(1);
    }
    int size[2][2];

    socklen_t len = sizeof(cliaddr);
    res = recvfrom(sd, &size, sizeof(size), 0, (struct sockaddr *)&cliaddr, &len);

    if(res < 0){
        perror("Error size");
        exit(1);
    }

    int matrix1[size[0][0]][size[0][1]];
    int matrix2[size[1][0]][size[1][1]];

    res = recvfrom(sd, &matrix1, sizeof(matrix1), 0, (struct sockaddr *)&cliaddr, &len);

    if(res < 0){
        perror("Error size");
        exit(1);
    }

    res = recvfrom(sd, &matrix2, sizeof(matrix2), 0, (struct sockaddr *)&cliaddr, &len);

    if(res < 0){
        perror("Error herheher");
        exit(1);
    }
    int product[size[0][0]][size[1][1]];
    for(int i = 0; i<size[0][0]; i++){
        for(int j = 0; j<size[0][1]; j++){
            product[i][j] = 0;
            int sum = 0;
            for(int k =  0; k<size[1][1]; k++){
                sum = sum + matrix1[i][k] * matrix2[k][j];
            }
            product[i][j] = sum;

        }
    }

    res = sendto(sd, &product, sizeof(product), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    if(res<0){
        perror("Error hrehkre");
        exit(1);
    }

    close(sd);
}