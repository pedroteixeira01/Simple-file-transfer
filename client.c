#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[]){

    int sfd, n = 0, b;
    char sendBuffer[100];
    char name[40];
    struct sockaddr_in server;
    FILE* archive;
    time_t start, end;

    if(argc != 2){
        perror("Syntax error");
        puts("use example: ./client <server_ip>\n");
        exit(1);
    }

    sfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr(argv[1]);

    b = connect(sfd, (struct sockaddr *)&server, sizeof(server));
    if (b == -1) {
        perror("Connection error");
        exit(1);
    }

    printf("\nEnter the file path with file type (i.e: /home/teste.txt) -> ");
    scanf("%s", name);
    archive = fopen(name, "rb");
    if(archive == NULL){
        perror("File error");
        exit(2);
    }

    time(&start);

    send(sfd, name, 40, 0);
    while((b = fread(sendBuffer, 1, sizeof(sendBuffer), archive)) > 0 ){
        send(sfd, sendBuffer, b, 0);
    }

    time(&end);

    puts("\nfile successfully sent.\n");
    printf("Transfer rate: %.2lf Mbps\n", (((sizeof(archive)*8)/1024)/1024)/difftime(end, start));

    fclose(archive);
    close(sfd);

    return 0;
}
