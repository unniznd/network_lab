#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdlib.h>

struct sockaddr_in servaddr;


int main(){

    int r1,c1, r2, c2;

    printf("Enter row of matrix 1:");
    scanf("%d",&r1);

    printf("Enter column of matrix 1:");
    scanf("%d",&c1);

    int matrix1[r1][c1];
    printf("Enter data of matrix 1:\n");
    for(int i = 0; i<r1; i++){
        for(int j = 0; j<c1; j++){
            printf("%d row and %d column", i, j);
            scanf("%d",&matrix1[i][j]);
        }
    }


    printf("Enter row of matrix 1:");
    scanf("%d",&r2);

    if(r2 != c1){
        perror("Matrix multiplication failed");
        exit(1);
    }

    printf("Enter column of matrix 1:");
    scanf("%d",&c2);

    int matrix2[r2][c2];
    printf("Enter data of matrix 1:\n");
    for(int i = 0; i<r2; i++){
        for(int j = 0; j<c2; j++){
            printf("%d row and %d column", i, j);
            scanf("%d",&matrix2[i][j]);
        }
    }

    int sd;

    sd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sd< 0){
        perror("Socket creation failed\n");
        exit(1);
    }


    bzero((char *)&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8000);

    inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);

    int size[2][2];

    size[0][0] = r1;
    size[0][1] = c1;
    size[1][0] = r2;
    size[1][1] = c2;

    int res = sendto(sd, &size, sizeof(size), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

    if(res < 0){
        perror("Error sending size of matrices\n");
        exit(1);
    }

    res = sendto(sd, &matrix1, sizeof(matrix1), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

    if(res < 0){
        perror("Error sending  matrix 1\n");
        exit(1);
    }

    res = sendto(sd, &matrix2, sizeof(matrix2), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

    if(res < 0){
        perror("Error sending  matrix 2\n");
        exit(1);
    }

    int product[r1][c2];

    res = recvfrom(sd, &product, sizeof(product),0, NULL, NULL);

    for(int i = 0;i<r1; i++){
        for(int j = 0; j<c2; j++){
            printf("%d ", product[i][j]);
        }
        printf("\n");
    }

    if(res == -1){
        perror("Error receiveing product\n");
        exit(1);
    
    }

    close(sd);

    return 0;
}