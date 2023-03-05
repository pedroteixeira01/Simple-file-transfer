#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(){

    int fd = 0, confd = 0, size , total=0;
    struct sockaddr_in server, client;
    socklen_t client_len;
    FILE* archive;
    char buff[1025], name[40];
    int num;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    
    puts("\nWaiting conections...\n");
    
    memset(&server, '0', sizeof(server));
    memset(buff, '0', sizeof(buff));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(5000);

    bind(fd, (struct sockaddr*)&server, sizeof(server));
    listen(fd, 10);

    while(1){
        confd = accept(fd, (struct sockaddr*)&client, &client_len);
        if (confd == -1) {
            perror("Accept error");
            continue;
        }
        
        getsockname(confd, (struct sockaddr*)&client, &client_len);
        printf("The ip %s connected to server\n", inet_ntoa(client.sin_addr));
        recv(confd, name, 40, 0);
        archive = fopen( name, "wb");

        if(archive != NULL){
            while((size = recv(confd, buff, 1024, 0)) > 0 ) {
                total += size;
                fwrite(buff, 1, size, archive);
            }

            puts("\n** Received file info **\n");
            printf("File name: %s\nFile size: %d B\n", name, total);
            
            if (size < 0) {
                perror("Receiving error");
            }

            fclose(archive);
        } else {
            perror("File error");
        }
        printf("The ip %s disconnected from server\n", inet_ntoa(client.sin_addr));
        close(confd);
    }
    close(fd);

    return 0;
}